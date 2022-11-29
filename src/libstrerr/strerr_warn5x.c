/* ISC license. */

/* MT-unsafe */

#include <skalibs/strerr.h>

void strerr_warn5x (char const *x1, char const *x2, char const *x3, char const *x4, char const *x5)
{
  char const *v[5] = { x1, x2, x3, x4, x5 } ;
  strerr_warnv(v, 5) ;
}
