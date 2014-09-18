/* ISC license. */

#include <errno.h>
#include <skalibs/iobuffer.h>

int iobufferk_nosys (iobufferk_ref k)
{
  (void)k ;
  return (errno = ENOSYS, -1) ;
}
