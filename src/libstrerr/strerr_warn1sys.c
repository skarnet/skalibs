/* ISC license. */

/* MT-unsafe */

#include <skalibs/strerr.h>

void strerr_warn1sys (char const *x1)
{
  strerr_warnvsys(&x1, 1) ;
}
