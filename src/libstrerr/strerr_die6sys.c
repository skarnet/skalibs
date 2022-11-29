/* ISC license. */

/* MT-unsafe */

#include <skalibs/strerr.h>

void strerr_die6sys (int e, char const *x1, char const *x2, char const *x3, char const *x4, char const *x5, char const *x6)
{
  char const *v[6] = { x1, x2, x3, x4, x5, x6 } ;
  strerr_dievsys(e, v, 6) ;
}
