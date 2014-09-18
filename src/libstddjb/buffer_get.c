/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>

int buffer_get (buffer *b, char *s, unsigned int len)
{
  unsigned int w = 0 ;
  register int r = buffer_getall(b, s, len, &w) ;
  return r == -1 ? errno == EPIPE ? (errno = 0, 0) : -1 :
         !r ? (errno = EWOULDBLOCK, -1) : (int)w ;
}
