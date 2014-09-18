/* ISC license. */

#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <skalibs/tai.h>

int tain_relative_from_timespec (tain_t *a, struct timespec const *ts)
{
  if (!tai_relative_from_timespec(tain_secp(a), ts)) return 0 ;
  a->nano = ts->tv_nsec ;
  return 1 ;
}
