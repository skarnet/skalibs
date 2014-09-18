/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/uint64.h>
#include <skalibs/tai.h>
#include <skalibs/djbtime.h>

#ifdef SKALIBS_FLAG_TZISRIGHT

int ltm64_from_tai (uint64 *u, tai_t const *t)
{
  *u = t->x - 10U ;
  return 1 ;
}

#else

int ltm64_from_tai (uint64 *u, tai_t const *t)
{
  return utc_from_tai(u, t) ;
}

#endif
