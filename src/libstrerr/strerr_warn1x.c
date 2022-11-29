/* ISC license. */

/* MT-unsafe */

#include <skalibs/strerr.h>

void strerr_warn1x (char const *x1)
{
  strerr_warnv(&x1, 1) ;
}
