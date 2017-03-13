/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>

ssize_t buffer_get (buffer *b, char *s, size_t len)
{
  size_t w = 0 ;
  int r = buffer_getall(b, s, len, &w) ;
  return r == -1 ? errno == EPIPE ? (errno = 0, w) : -1 :
         !r ? (errno = EWOULDBLOCK, -1) : w ;
}
