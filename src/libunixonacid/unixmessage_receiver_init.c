/* ISC license. */

#include <errno.h>
#include <skalibs/cbuffer.h>
#include <skalibs/stralloc.h>
#include <skalibs/unixmessage.h>

int unixmessage_receiver_init (unixmessage_receiver_t *b, int fd, char *mainbuf, unsigned int mainlen, char *auxbuf, unsigned int auxlen)
{
  if (!cbuffer_init(&b->mainb, mainbuf, mainlen)
   || !cbuffer_init(&b->auxb, auxbuf, auxlen)) return 0 ;
  b->fd = fd ;
  b->mainlen = b->auxlen = 0 ;
  b->maindata = stralloc_zero ;
  b->auxdata = stralloc_zero ;
  b->fds_ok = 3 ;
  return 1 ;
}
