/* ISC license. */

/* MT-unsafe */

#include <skalibs/strerr.h>

void strerr_die1x (int e, char const *x1)
{
  strerr_diev(e, &x1, 1) ;
}
