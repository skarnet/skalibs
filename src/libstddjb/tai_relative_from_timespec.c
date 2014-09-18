/* ISC license. */

#include <sys/types.h>
#include <time.h>
#include <skalibs/tai.h>

int tai_relative_from_timespec (tai_t *t, struct timespec const *ts)
{
  tai_u64(t, ts->tv_sec) ;
  return 1 ;
}
