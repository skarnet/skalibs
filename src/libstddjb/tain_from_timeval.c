/* ISC license. */

#include <sys/time.h>
#include <errno.h>
#include <skalibs/tai.h>

int tain_from_timeval (tain_t *a, struct timeval const *tv)
{
  if (!tai_from_timeval(tain_secp(a), tv)) return 0 ;
  a->nano = 1000 * tv->tv_usec ;
  return 1 ;
}
