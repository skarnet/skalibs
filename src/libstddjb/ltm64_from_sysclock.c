/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/uint64.h>
#include <skalibs/djbtime.h>

#ifdef SKALIBS_FLAG_CLOCKISTAI

#include <skalibs/tai.h>

int ltm64_from_sysclock (uint64 *u)
{
  tai_t t = { *u + 10U } ;
  return ltm64_from_tai(u, &t) ;
}

#else

int ltm64_from_sysclock (uint64 *u)
{
  return ltm64_from_utc(u) ;
}

#endif
