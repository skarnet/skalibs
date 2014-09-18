/* ISC license. */

#include <errno.h>
#include <skalibs/iobuffer.h>

int iobuffer_flush (iobuffer_ref b)
{
  if (b->isk)
  {
    if (iobufferk_flush(&b->x.k)) return 1 ;
    if (errno != ENOSYS || !iobuffer_salvage(b)) return 0 ;
  }
  return iobufferu_flush(&b->x.u) ;
}
