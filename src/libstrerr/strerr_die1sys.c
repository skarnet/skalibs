/* ISC license. */

/* MT-unsafe */

#include <skalibs/strerr.h>

void strerr_die1sys (int e, char const *x1)
{
  strerr_dievsys(e, &x1, 1) ;
}
