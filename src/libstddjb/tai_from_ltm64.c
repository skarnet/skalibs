/* ISC license. */

#include <skalibs/uint64.h>
#include <skalibs/tai.h>
#include <skalibs/djbtime.h>
#include "djbtime-internal.h"

int tai_from_ltm64 (tai_t *t, uint64 u)
{
  switch (skalibs_tzisright())
  {
    case 1 : return tai_u64(t, u + 10U) ;
    case 0 : return tai_from_utc(t, u) ;
    default : return 0 ;
  }
}
