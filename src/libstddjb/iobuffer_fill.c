/* ISC license. */

#include <sys/types.h>
#include <errno.h>
#include <skalibs/iobuffer.h>

ssize_t iobuffer_fill (iobuffer_ref b)
{
  if (b->isk)
  {
    ssize_t r = iobufferk_fill(&b->x.k) ;
    if (r >= 0 || errno != ENOSYS || !iobuffer_salvage(b)) return r ;
  }
  return iobufferu_fill(&b->x.u) ;
}
