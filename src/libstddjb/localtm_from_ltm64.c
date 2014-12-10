/* ISC license. */

/* OpenBSD needs that for EOVERFLOW. wtfbsdseriously */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <sys/types.h>
#include <errno.h>
#include <time.h>
#include <skalibs/uint64.h>
#include <skalibs/tai.h>
#include <skalibs/djbtime.h>

int localtm_from_ltm64 (struct tm *l, uint64 uu, int tz)
{
  if (uu < TAI_MAGIC) return (errno = EINVAL, 0) ;
  uu -= TAI_MAGIC ;
  if (uu > 0xFFFFFFFFUL) return (errno = EOVERFLOW, 0) ;
  {
    time_t u = (time_t)uu ;
    if (tz ? !localtime_r(&u, l) : !gmtime_r(&u, l)) return 0 ;
  }
  return 1 ;
}
