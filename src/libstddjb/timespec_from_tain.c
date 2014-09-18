/* ISC license. */

#include <sys/types.h>
#include <time.h>
#include <skalibs/tai.h>

int timespec_from_tain (struct timespec *ts, tain_t const *a)
{
  struct timespec tmp ;
  if (!timespec_from_tai(&tmp, tain_secp(a))) return 0 ;
  ts->tv_sec = tmp.tv_sec ;
  ts->tv_nsec = a->nano ;
  return 1 ;
}
