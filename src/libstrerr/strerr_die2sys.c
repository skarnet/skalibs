/* ISC license. */

/* MT-unsafe */

#include <skalibs/strerr.h>

void strerr_die2sys (int e, char const *x1, char const *x2)
{
  char const *v[2] = { x1, x2 } ;
  strerr_dievsys(e, v, 2) ;
}
