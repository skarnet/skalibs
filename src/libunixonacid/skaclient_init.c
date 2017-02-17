/* ISC license. */

#include <sys/types.h>
#include <skalibs/kolbak.h>
#include <skalibs/skaclient.h>
#include <skalibs/unixmessage.h>
#include "skaclient-internal.h"

int skaclient_init (
  skaclient_t *a,
  int fd,
  char *bufss,
  size_t bufsn,
  char *auxbufss,
  size_t auxbufsn,
  char *bufas,
  size_t bufan,
  char *auxbufas,
  size_t auxbufan,
  kolbak_closure_t *q,
  size_t qlen,
  char const *before,
  size_t beforelen)
{
  unixmessage_t msg = { .s = (char *)before, .len = beforelen, .fds = 0, .nfds = 0 } ;
  if (!unixmessage_receiver_init(&a->syncin, fd, bufss, bufsn, auxbufss, auxbufsn)
   || !unixmessage_receiver_init(&a->asyncin, -1, bufas, bufan, auxbufas, auxbufan)
   || !kolbak_queue_init(&a->kq, q, qlen)) return 0 ;
  unixmessage_sender_init(&a->syncout, fd) ;
  unixmessage_sender_init(&a->asyncout, -1) ;
  if (!unixmessage_put(&a->syncout, &msg)) return 0 ;
  return 1 ;
}
