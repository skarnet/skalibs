/* ISC license. */

/* MT-unsafe */

#include <skalibs/strerr.h>

void strerr_warn4sys (char const *x1, char const *x2, char const *x3, char const *x4)
{
  char const *v[4] = { x1, x2, x3, x4 } ;
  strerr_warnvsys(v, 4) ;
}
