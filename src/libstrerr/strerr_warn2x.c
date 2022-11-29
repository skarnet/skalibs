/* ISC license. */

/* MT-unsafe */

#include <skalibs/strerr.h>

void strerr_warn2x (char const *x1, char const *x2)
{
  char const *v[2] = { x1, x2 } ;
  strerr_warnv(v, 2) ;
}
