/* ISC license. */

/* MT-unsafe */

#include <skalibs/strerr.h>

void strerr_die10sys (int e, char const *x1, char const *x2, char const *x3, char const *x4, char const *x5, char const *x6, char const *x7, char const *x8, char const *x9, char const *x10)
{
  char const *v[10] = { x1, x2, x3, x4, x5, x6, x7, x8, x9, x10 } ;
  strerr_dievsys(e, v, 10) ;
}
