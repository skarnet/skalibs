/* ISC license. */

/* MT-unsafe */

#include <skalibs/strerr.h>

void strerr_die7sys (int e, char const *x1, char const *x2, char const *x3, char const *x4, char const *x5, char const *x6, char const *x7)
{
  char const *v[7] = { x1, x2, x3, x4, x5, x6, x7 } ;
  strerr_dievsys(e, v, 7) ;
}
