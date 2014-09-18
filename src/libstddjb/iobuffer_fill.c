/* ISC license. */

#include <errno.h>
#include <skalibs/iobuffer.h>

int iobuffer_fill (iobuffer_ref b)
{
  if (b->isk)
  {
    register int r = iobufferk_fill(&b->x.k) ;
    if (r >= 0 || errno != ENOSYS || !iobuffer_salvage(b)) return r ;
  }
  return iobufferu_fill(&b->x.u) ;
}
