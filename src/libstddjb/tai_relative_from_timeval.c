/* ISC license. */

#include <sys/time.h>
#include <skalibs/tai.h>

int tai_relative_from_timeval (tai_t *t, struct timeval const *tv)
{
  tai_u64(t, tv->tv_sec) ;
  return 1 ;
}
