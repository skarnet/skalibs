/* ISC license. */

/* MT-unsafe */

#include <time.h>
#include <skalibs/uint64.h>
#include <skalibs/tai.h>

int tai_now (tai_t *t)
{
  register uint64 u = TAI_MAGIC + time(0) ;
  return tai_from_sysclock(t, u) ;
}
