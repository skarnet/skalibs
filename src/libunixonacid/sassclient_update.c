/* ISC license. */

#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

#include <skalibs/uint32.h>
#include <skalibs/textclient.h>
#include <skalibs/gensetdyn.h>
#include <skalibs/genqdyn.h>
#include <skalibs/sassclient.h>
#include "sassclient-internal.h"

#include <skalibs/posixishard.h>

static int sassclient_msghandler (struct iovec const *v, void *aux)
{
  sassclient *a = aux ;
  char const *s = v->iov_base ;
  int e ;
  sassclient_data *p ;
  uint32_t id ;
  char res[8] ;
  if (v->iov_len < 8) return (errno = EPROTO, 0) ;
  uint32_unpack_big(s, &id) ;
  memcpy(res, s, 4) ; s += 4 ;
  p = GENSETDYN_P(sassclient_data, &a->store, id) ;
  if (memcmp(s, "\0\0\0", 4))
  {
    if (v->iov_len != 8) return (errno = EPROTO, 0) ;
    memcpy(res + 4, s, 4) ;
  }
  else
  {
    e = (*p->cb)(s + 8, v->iov_len - 8, p->data) ;
    uint32_pack_big(res + 4, e) ;
  }
  e = pthread_mutex_lock(&a->results_mutex) ;
  if (e) return (errno = e, 0) ;
  if (!genqdyn_push(&a->results, res))
  {
    pthread_mutex_unlock(&a->results_mutex) ;
    return 0 ;
  }
  pthread_mutex_unlock(&a->results_mutex) ;
  if (!gensetdyn_delete(&a->store, id)) return 0 ;
  return 1 ;
}

int sassclient_update (sassclient *a)
{
  int e = pthread_mutex_lock(&a->connection_mutex) ;
  if (e) return (errno = e, -1) ;
  e = textclient_update(&a->connection, &sassclient_msghandler, a) ;
  pthread_mutex_unlock(&a->connection_mutex) ;
  return e < 0 ? -1 : !!e ;
}
