/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/tai.h>

#ifdef SKALIBS_HASCLOCKMON

#include <time.h>

int tain_clockmon_init (tain_t *offset)
{
  tain_t a, b ;
  struct timespec ts ;
  if (!tain_sysclock(&a)) return 0 ;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) < 0) return 0 ;
  if (!tain_from_timespec(&b, &ts)) return 0 ;
  tain_add(&a, &a, &tain_nano500) ;
  tain_sub(offset, &a, &b) ;
  return 1 ;
}

int tain_clockmon (tain_t *a, tain_t const *offset)
{
  struct timespec ts ;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) < 0) return 0 ;
  if (!tain_from_timespec(a, &ts)) return 0 ;
  tain_add(a, a, offset) ;
  return 1 ;
}

#else

#include <errno.h>

int tain_clockmon_init (tain_t *offset)
{
  (void)offset ;
  return (errno = ENOSYS, 0) ;
}

int tain_clockmon (tain_t *a, tain_t const *offset)
{
  (void)a ; (void)offset ;
  return (errno = ENOSYS, 0) ;
}

#endif
