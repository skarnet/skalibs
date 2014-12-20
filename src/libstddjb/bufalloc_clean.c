/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/bufalloc.h>

void bufalloc_clean (register bufalloc *ba)
{
  if (ba->p)
  {
    byte_copy(ba->x.s, ba->x.len - ba->p, ba->x.s + ba->p) ;
    ba->x.len -= ba->p ;
    ba->p = 0 ;
  }
}
