/* ISC license. */

/* MT-unsafe */

#include <skalibs/strerr.h>

void strerr_warn3sys (char const *x1, char const *x2, char const *x3)
{
  char const *v[3] = { x1, x2, x3 } ;
  strerr_warnvsys(v, 3) ;
}
