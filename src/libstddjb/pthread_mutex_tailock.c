/* ISC license. */

#include <errno.h>
#include <time.h>
#include <pthread.h>

#include <skalibs/sysdeps.h>
#include <skalibs/tai.h>
#include <skalibs/pthread.h>

int pthread_mutex_tailock (pthread_mutex_t *mtx, tain const *deadline, tain *stamp)
{
  struct timespec ts ;
  tain tto ;
  tain_sub(&tto, deadline, stamp) ;
  if (!timespec_from_tain_relative(&ts, &tto)) return errno ;
#ifdef SKALIBS_HASPTHREADMUTEXCLOCKLOCK
  if (&tain_now != &tain_wallclock_read)
    return pthread_mutex_clocklock(mtx, CLOCK_MONOTONIC, &ts) ;
  else
#else
  return pthread_mutex_timedlock(mtx, &ts) ;
#endif
}
