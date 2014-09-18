/* ISC license. */

#include <sys/time.h>
#include <skalibs/tai.h>

int timeval_from_tai (struct timeval *tv, tai_t const *t)
{
  tai_t trel ;
  tai_u64(&trel, tai_sec(t) - TAI_MAGIC) ;
  return timeval_from_tai_relative(tv, &trel) ;
}
