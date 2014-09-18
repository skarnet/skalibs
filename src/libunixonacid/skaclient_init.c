/* ISC license. */

#include <skalibs/kolbak.h>
#include <skalibs/skaclient.h>
#include <skalibs/unixmessage.h>
#include "skaclient-internal.h"

int skaclient_init (
  skaclient_t *a,
  int fd,
  char *bufss,
  unsigned int bufsn,
  char *auxbufss,
  unsigned int auxbufsn,
  char *bufas,
  unsigned int bufan,
  char *auxbufas,
  unsigned int auxbufan,
  kolbak_closure_t *q,
  unsigned int qlen,
  char const *before,
  unsigned int beforelen)
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
