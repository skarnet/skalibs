/* ISC license. */

#include <skalibs/uint64.h>
#include <skalibs/tai.h>
#include <skalibs/djbtime.h>
#include "djbtime-internal.h"

int utc_from_tai (uint64 *u, tai_t const *t)
{
  uint64 tt = t->x - 10 ;
  if (leapsecs_sub(&tt) < 0) return 0 ;
  *u = tt ;
  return 1 ;
}
