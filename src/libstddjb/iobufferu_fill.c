/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/iobuffer.h>

ssize_t iobufferu_fill (iobufferu *b)
{
  ssize_t r = buffer_fill(&b->b[0]) ;
  b->b[1].c.n = b->b[0].c.n ;
  return r ;
}
