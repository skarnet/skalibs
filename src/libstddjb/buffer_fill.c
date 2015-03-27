/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>

int buffer_fill (buffer *b)
{
  siovec_t v[2] ;
  register int r ;
  if (buffer_isfull(b)) return (errno = ENOBUFS, -1) ;
  buffer_wpeek(b, v) ;
  r = (*b->op)(b->fd, v, 2) ;
  if (r <= 0) return r ;
  buffer_wseek(b, r) ;
  return r ;
}
