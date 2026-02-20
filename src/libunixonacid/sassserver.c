/* ISC license. */

#include <sys/uio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include <skalibs/uint32.h>
#include <skalibs/alloc.h>
#include <skalibs/error.h>
#include <skalibs/strerr.h>
#include <skalibs/tai.h>
#include <skalibs/iopause.h>
#include <skalibs/gensetdyn.h>
#include <skalibs/avltree.h>
#include <skalibs/textmessage.h>
#include <skalibs/textclient.h>
#include <skalibs/sassserver.h>

typedef struct sassserver_query_s sassserver_query, sassserver_query_ref ;
struct sassserver_query_s
{
  uint32_t id ;
  tain deadline ;
  void *data ;
} ;

static sassserver_send_func_ref sassserver_sendf ;
static sassserver_cancel_func_ref sassserver_cancelf ;
static size_t sassserver_datasize ;

static gensetdyn sassserver_queries = GENSETDYN_INIT(sassserver_query, 8, 3, 8) ;
#define SASSSERVER_QUERY(i) GENSETDYN_P(sassserver_query, &sassserver_queries, (i))

static void *sassserver_deadline_dtok (uint32_t d, void *aux)
{
  return &GENSETDYN_P(sassserver_query, (gensetdyn *)aux, d)->deadline ;
}

void *sassserver_data (uint32_t handle)
{
  return SASSSERVER_QUERY(handle)->data ;
}

static int sassserver_deadline_cmp (void const *a, void const *b, void *aux)
{
  tain const *aa = a ;
  tain const *bb = b ;
  (void)aux ;
  return tain_less(aa, bb) ? -1 : tain_less(bb, aa) ;
}

static avltree sassserver_by_deadline = AVLTREE_INIT(8, 3, 8, &sassserver_deadline_dtok, &sassserver_deadline_cmp, &sassserver_queries) ;

static void *sassserver_id_dtok (uint32_t d, void *aux)
{
  return &GENSETDYN_P(sassserver_query, (gensetdyn *)aux, d)->id ;
}

static int sassserver_id_cmp (void const *a, void const *b, void *aux)
{
  uint32_t const *aa = a ;
  uint32_t const *bb = b ;
  (void)aux ;
  return *aa < *bb ? -1 : *aa > *bb ;
}

static avltree sassserver_by_id = AVLTREE_INIT(8, 3, 8, &sassserver_id_dtok, &sassserver_id_cmp, &sassserver_queries) ;

static void sassserver_sync_answer (int e)
{
  char pack[4] ;
  uint32_pack_big(pack, (uint32_t)e) ;
  if (!textmessage_put(textmessage_sender_1, pack, 4))
    strerr_diefu1sys(111, "textmessage_put") ;
}

static void sassserver_remove (uint32_t handle)
{
  sassserver_query *p = SASSSERVER_QUERY(handle) ;
  avltree_delete(&sassserver_by_deadline, &p->deadline) ;
  avltree_delete(&sassserver_by_id, &p->id) ;
  gensetdyn_delete(&sassserver_queries, handle) ;
}

void sassserver_async_failure (uint32_t handle, int e)
{
  sassserver_query *p = SASSSERVER_QUERY(handle) ;
  char pack[8] ;
  uint32_pack_big(pack, p->id) ;
  uint32_pack_big(pack + 4, (uint32_t)e) ;
  if (!textmessage_put(textmessage_sender_x, pack, 8))
    strerr_diefu1sys(111, "textmessage_put") ;
  sassserver_remove(handle) ;
}

void sassserver_async_successv (uint32_t handle, struct iovec const *v, unsigned int n)
{
  sassserver_query *p = SASSSERVER_QUERY(handle) ;
  char pack[8] = "\0\0\0\0\0\0\0" ;
  struct iovec vv[n+1] ;
  vv[0].iov_base = pack ; vv[0].iov_len = 8 ;
  for (unsigned int i = 0 ; i < n ; i++) vv[i+1] = v[i] ;
  uint32_pack_big(pack, p->id) ;
  if (!textmessage_putv(textmessage_sender_x, vv, n+1))
    strerr_diefu1sys(111, "textmessage_putv") ;
  sassserver_remove(handle) ;
}

void sassserver_async_success (uint32_t handle, char const *s, size_t len)
{
  struct iovec v = { .iov_base = (char *)s, .iov_len = len } ;
  sassserver_async_successv(handle, &v, 1) ;
}

static inline void sassserver_uniquify (tain *deadline)
{
  static tain const nanosec = { .sec = TAI_ZERO, .nano = 1 } ;
  uint32_t dummy ;
  while (avltree_search(&sassserver_by_deadline, deadline, &dummy))
    tain_add(deadline, deadline, &nanosec) ;
}

static int sassserver_parse_protocol (struct iovec const *v, void *aux)
{
  char const *s = v->iov_base ;
  size_t vlen = v->iov_len ;
  (void)aux ;
  if (vlen-- < 5) strerr_dief1x(100, "invalid client request") ;
  switch (*s++)
  {
    case '-' : /* cancel */
    {
      uint32_t handle, id ;
      if (vlen != 4) strerr_dief1x(100, "invalid client request") ;
      uint32_unpack_big(s, &id) ;
      if (!avltree_search(&sassserver_by_id, &id, &handle)) sassserver_sync_answer(EINVAL) ;
      (*sassserver_cancelf)(SASSSERVER_QUERY(handle)->data) ;
      sassserver_remove(handle) ;
      sassserver_sync_answer(0) ;
      break ;
    }
    case '+' : /* send */
    {
      sassserver_query *p ;
      uint32_t handle ;
      uint32_t timeout ;
      uint32_t opcode ;
      uint32_t len ;
      int e ;
      if (vlen < 16) strerr_dief1x(100, "invalid client request") ;
      if (!gensetdyn_new(&sassserver_queries, &handle)) strerr_diefu1sys(111, "gensetdyn_new") ;
      p = SASSSERVER_QUERY(handle) ;
      uint32_unpack_big(s, &p->id) ; s += 4 ; vlen -= 4 ;
      uint32_unpack_big(s, &timeout) ; s += 4 ; vlen -= 4 ;
      uint32_unpack_big(s, &opcode) ; s += 4 ; vlen -= 4 ;
      uint32_unpack_big(s, &len) ; s += 4 ; vlen -= 4 ;
      if (len != vlen) strerr_dief1x(100, "invalid client request") ;
      if (timeout)
      {
        if (!tain_from_millisecs(&p->deadline, timeout)) strerr_dief1x(100, "invalid client request") ;
        tain_add_g(&p->deadline, &p->deadline) ;
      }
      else tain_add_g(&p->deadline, &tain_infinite_relative) ;
      sassserver_uniquify(&p->deadline) ;
      if (!avltree_insert(&sassserver_by_deadline, handle)) strerr_diefu1sys(111, "avltree_insert") ;
      if (!avltree_insert(&sassserver_by_id, handle)) strerr_diefu1sys(111, "avltree_insert") ;
      if (!p->data)
      {
        p->data = alloc(sassserver_datasize) ;
        if (!p->data) strerr_diefu1sys(111, "alloc") ;
      }
      e = (*sassserver_sendf)(p->data, handle, opcode, s, len) ;
      if (e) sassserver_remove(handle) ;
      sassserver_sync_answer(e) ;
      break ;
    }
    default : strerr_dief1x(100, "invalid client request") ;
  }
  return 1 ;
}

void sassserver_init (char const *banner1, char const *banner2, sassserver_send_func_ref sendf, sassserver_cancel_func_ref cancelf, size_t datasize, tain const *deadline, tain *stamp)
{
  if (!textclient_server_01x_init(banner1, strlen(banner1), banner2, strlen(banner2), deadline, stamp))
    strerr_diefu1sys(111, "sync with client") ;
  sassserver_sendf = sendf ;
  sassserver_cancelf = cancelf ;
}

unsigned int sassserver_prepare_iopause (iopause_fd *x, tain *deadline)
{
  uint32_t i ;
  if (avltree_min(&sassserver_by_deadline, &i)) tain_earliest1(deadline, &SASSSERVER_QUERY(i)->deadline) ;
  x[0].fd = 0 ;
  x[0].events = IOPAUSE_READ ;
  x[1].fd = 1 ;
  x[1].events = textmessage_sender_isempty(textmessage_sender_1) ? 0 : IOPAUSE_WRITE ;
  x[2].fd = textmessage_sender_fd(textmessage_sender_x) ;
  x[2].events = textmessage_sender_isempty(textmessage_sender_x) ? 0 : IOPAUSE_WRITE ;
  return 3 ;
}

void sassserver_timeout (void)
{
  uint32_t i ;
  while (avltree_min(&sassserver_by_deadline, &i))
  {
    sassserver_query *p = SASSSERVER_QUERY(i) ;
    if (tain_future(&p->deadline)) break ;
    avltree_delete(&sassserver_by_deadline, &p->deadline) ;
    avltree_delete(&sassserver_by_id, &p->id) ;
    (*sassserver_cancelf)(p->data) ;
    sassserver_async_failure(p->id, ETIMEDOUT) ;
    gensetdyn_delete(&sassserver_queries, i) ;
  }
}

int sassserver_event (iopause_fd const *x)
{
  if (x[1].revents & IOPAUSE_WRITE)
    if (!textmessage_sender_flush(textmessage_sender_1) && !error_isagain(errno))
      strerr_diefu1sys(111, "flush stdout") ;
  if (x[2].revents & IOPAUSE_WRITE)
    if (!textmessage_sender_flush(textmessage_sender_x) && !error_isagain(errno))
      strerr_diefu1sys(111, "flush asyncout") ;

  if (!textmessage_receiver_isempty(textmessage_receiver_0) || x[0].revents & IOPAUSE_READ)
  {
    if (textmessage_handle(textmessage_receiver_0, &sassserver_parse_protocol, 0) == -1)
    {
      if (errno != EPIPE) strerr_diefu1sys(111, "read messages from client") ;
      return 1 ;
    }
  }
  return 0 ;
}
