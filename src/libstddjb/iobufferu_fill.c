/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/iobuffer.h>

int iobufferu_fill (iobufferu_ref b)
{
  register int r = buffer_fill(&b->b[0]) ;
  b->b[1].c.n = b->b[0].c.n ;
  return r ;
}
