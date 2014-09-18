/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/uint64.h>
#include <skalibs/tai.h>
#include <skalibs/djbtime.h>

#ifdef SKALIBS_FLAG_TZISRIGHT

int tai_from_ltm64 (tai_t *t, uint64 u)
{
  tai_u64(t, u + 10U) ;
  return 1 ;
}

#else

int tai_from_ltm64 (tai_t *t, uint64 u)
{
  return tai_from_utc(t, u) ;
}

#endif
