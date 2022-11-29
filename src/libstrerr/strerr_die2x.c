/* ISC license. */

/* MT-unsafe */

#include <skalibs/strerr.h>

void strerr_die2x (int e, char const *x1, char const *x2)
{
  char const *v[2] = { x1, x2 } ;
  strerr_diev(e, v, 2) ;
}
