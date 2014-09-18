/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/tai.h>

#ifdef SKALIBS_FLAG_CLOCKISTAI

int tai_from_sysclock (tai_t *t, uint64 u)
{
  tai_u64(t, u + 10U) ;
  return 1 ;
}

#else

#include <skalibs/djbtime.h>

int tai_from_sysclock (tai_t *t, uint64 u)
{
  return tai_from_utc(t, u) ;
}

#endif
