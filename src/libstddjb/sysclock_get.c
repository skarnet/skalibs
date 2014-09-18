/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/sysdeps.h>
#include <skalibs/tai.h>

#ifdef SKALIBS_FLAG_USERT
# ifndef SKALIBS_HASCLOCKRT
#  undef SKALIBS_FLAG_USERT
#  warning "SKALIBS_FLAG_USERT set but SKALIBS_HASCLOCKRT not found. Clearing SKALIBS_FLAG_USERT."
# endif
#endif

#ifdef SKALIBS_FLAG_USERT

#include <time.h>

int sysclock_get (tain_t *a)
{
  tain_t aa ;
  struct timespec now ;
  if (clock_gettime(CLOCK_REALTIME, &now) < 0) return 0 ;
  if (!tain_from_timespec(&aa, &now)) return 0 ;
  tain_add(a, &aa, &tain_nano500) ;
  return 1 ;
}

#else

#include <sys/time.h>

int sysclock_get (tain_t *a)
{
  tain_t aa ;
  struct timeval now ;
  if (gettimeofday(&now, 0) < 0) return 0 ;
  if (!tain_from_timeval(&aa, &now)) return 0 ;
  tain_add(a, &aa, &tain_nano500) ;
  return 1 ;
}

#endif
