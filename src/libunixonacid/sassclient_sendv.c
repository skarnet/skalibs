/* ISC license. */

#include <sys/uio.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>
#include <limits.h>
#include <pthread.h>

#include <skalibs/uint32.h>
#include <skalibs/tai.h>
#include <skalibs/siovec.h>
#include <skalibs/gensetdyn.h>
#include <skalibs/textclient.h>
#include <skalibs/sassclient.h>
#include "sassclient-internal.h"

int sassclient_sendv (sassclient *a, uint32_t *cid, uint32_t flags, uint32_t timeout, uint32_t opcode, struct iovec const *vv, unsigned int n, sassclient_cb_func_ref cb, void *data, tain const *deadline, tain *stamp)
{
  size_t len = siovec_len(vv, n) ;
  uint32_t id ;
  int e ;
  struct iovec answer ;
  sassclient_data *p ;
  char pack[21] = "+" ;
  struct iovec v[1 + n] ;
  if (len + 11 > UINT32_MAX) return (errno = ENAMETOOLONG, 0) ;

  {
    struct timespec ts ;
    tain diff ;
    tain_sub(&diff, deadline, stamp) ;
    if (!timespec_from_tain_relative(&ts, &diff)) return 0 ;
    e = pthread_mutex_timedlock(&a->connection_mutex, &ts) ;
//    e = pthread_mutex_clocklock(&a->connection_mutex, CLOCK_MONOTONIC, &ts) ;
    if (e) return (errno = e, 0) ;
  }

  if (!gensetdyn_new(&a->store, &id)) goto err ;
  v[0].iov_base = pack ;
  v[0].iov_len = 17 ;
  for (unsigned int i = 0 ; i < n ; i++) v[i+1] = vv[i] ;
  uint32_pack_big(pack + 1, id) ;
  uint32_pack_big(pack + 5, flags) ;
  uint32_pack_big(pack + 9, timeout) ;
  uint32_pack_big(pack + 13, opcode) ;
  uint32_pack_big(pack + 17, len) ;
  if (!textclient_exchangev(&a->connection, v, 1 + n, &answer, deadline, stamp)) { e = errno ; goto err0 ; }
  if (answer.iov_len == 1) { e = *(unsigned char *)answer.iov_base ; goto err0 ; }
  if (answer.iov_len != 5 || *(unsigned char *)answer.iov_base) { e = EPROTO ; goto err0 ; }
  p = GENSETDYN_P(sassclient_data, &a->store, id) ;
  p->cb = cb ;
  p->data = data ;
  pthread_mutex_unlock(&a->connection_mutex) ;
  *cid = id ;
  return 1 ;

 err0:
  gensetdyn_delete(&a->store, id) ;
  errno = e ;
 err:
  pthread_mutex_unlock(&a->connection_mutex) ;
  return 0 ;
}
