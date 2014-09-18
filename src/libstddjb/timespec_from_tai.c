/* ISC license. */

#include <sys/types.h>
#include <time.h>
#include <skalibs/tai.h>

int timespec_from_tai (struct timespec *ts, tai_t const *t)
{
  tai_t trel ;
  tai_u64(&trel, tai_sec(t) - TAI_MAGIC) ;
  return timespec_from_tai_relative(ts, &trel) ;
}
