/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/cbuffer.h>

int buffer_fill (buffer *b)
{
  siovec_t v[2] ;
  register int r ;
  if (buffer_isfull(b)) return (errno = ENOBUFS, -1) ;
  buffer_wpeek(b, v) ;
  r = (*b->op)(b->fd, v, 2) ;
  if (r <= 0) return r ;
  cbuffer_WSEEK(&b->c, r) ;
  return r ;
}
