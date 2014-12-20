/* ISC license. */

#include <errno.h>
#include <skalibs/iobuffer.h>

int iobufferk_nosys (iobufferk *k)
{
  (void)k ;
  return (errno = ENOSYS, -1) ;
}
