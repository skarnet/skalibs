/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/iobuffer.h>

int iobufferu_flush (iobufferu *b)
{
  register int r = buffer_flush(&b->b[1]) ;
  b->b[0].c.p = b->b[1].c.p ;
  return r ;
}
