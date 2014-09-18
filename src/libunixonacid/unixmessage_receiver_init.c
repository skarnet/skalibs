/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/cbuffer.h>
#include <skalibs/stralloc.h>
#include <skalibs/unixmessage.h>

int unixmessage_receiver_init (unixmessage_receiver_t *b, int fd, char *mainbuf, unsigned int mainlen, char *auxbuf, unsigned int auxlen)
{
  if (mainlen < 9 || auxlen < UNIXMESSAGE_MAXFDS * sizeof(int) + 1) return (errno = EINVAL, 0) ;
  if (!cbuffer_init(&b->auxb, auxbuf, auxlen)) return 0 ;
  if (!buffer_init_aux(&b->mainb, &unixmessage_read, fd, mainbuf, mainlen, &b->auxb)) return 0 ;
  b->mainlen = b->auxlen = b->auxw = 0 ;
  b->data = stralloc_zero ;
  return 1 ;
}
