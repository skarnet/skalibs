/* ISC license. */

#include <skalibs/uint64.h>
#include <skalibs/tai.h>
#include <skalibs/djbtime.h>
#include "djbtime-internal.h"

int ltm64_from_tai (uint64 *u, tai_t const *t)
{
  switch (skalibs_tzisright())
  {
    case 1 : *u = t->x - 10U ; return 1 ;
    case 0 : return utc_from_tai(u, t) ;
    default : return 0 ;
  }
}
