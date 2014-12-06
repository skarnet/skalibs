/* ISC license. */

#include <skalibs/cbuffer.h>
#include <skalibs/siovec.h>
#include <skalibs/buffer.h>

int buffer_flush (buffer *b)
{
  for (;;)
  {
    siovec_t v[2] ;
    register int r ;
    buffer_rpeek(b, v) ;
    if (!v[0].len && !v[1].len) break ;
    r = (*b->op)(b->fd, v, 2) ;
    if (r <= 0) return 0 ;
    cbuffer_RSEEK(&b->c, r) ;
  }
  return 1 ;
}
