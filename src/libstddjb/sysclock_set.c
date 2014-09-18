/* ISC license. */

/* MT-unsafe */

#include <skalibs/config.h>
#include <skalibs/sysdeps.h>

#ifdef SKALIBS_FLAG_USERT
# ifndef SKALIBS_HASCLOCKRT
#  undef SKALIBS_FLAG_USERT
#  warning "SKALIBS_FLAG_USERT set but SKALIBS_HASCLOCKRT not found. Clearing SKALIBS_FLAG_USERT."
# endif
#endif

#ifndef SKALIBS_FLAG_USERT
# ifndef SKALIBS_HASSETTIMEOFDAY
#  error "SKALIBS_FLAG_USERT clear but SKALIBS_HASSETTIMEOFDAY not found. How do your set your system clock?"
# endif
#endif


#ifdef SKALIBS_FLAG_USERT

#include <time.h>
#include <skalibs/tai.h>

int sysclock_set (tain_t const *a)
{
  struct timespec now ;
  tain_t aa ;
  tain_add(&aa, a, &tain_nano500) ;
  if (!timespec_from_tain(&now, &aa)) return 0 ;
  if (clock_settime(CLOCK_REALTIME, &now) < 0) return 0 ;
  return 1 ;
}

#else

#include <skalibs/nonposix.h>
#include <sys/time.h>
#include <skalibs/tai.h>

int sysclock_set (tain_t const *a)
{
  struct timeval now ;
  tain_t aa ;
  tain_add(&aa, a, &tain_nano500) ;
  if (!timeval_from_tain(&now, &aa)) return 0 ;
  if (settimeofday(&now, 0) < 0) return 0 ;
  return 1 ;
}

#endif
