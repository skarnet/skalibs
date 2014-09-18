/* ISC license. */

#include <skalibs/tai.h>

double tain_frac (tain_t const *t)
{
  return t->nano * 0.000000001 ;
}
