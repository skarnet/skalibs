/* ISC license. */

#include <skalibs/alloc.h>
#include <skalibs/iobuffer.h>

void iobufferu_finish (iobufferu *b)
{
  alloc_free(b->buf) ;
}
