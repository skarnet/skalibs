/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/tai.h>

#ifdef SKALIBS_FLAG_CLOCKISTAI

int sysclock_from_tai (uint64 *u, tai_t const *t)
{
  *u = t->x - 10U ;
  return 1 ;
}

#else

#include <skalibs/djbtime.h>

int sysclock_from_tai (uint64 *u, tai_t const *t)
{
  return utc_from_tai(u, t) ;
}

#endif
