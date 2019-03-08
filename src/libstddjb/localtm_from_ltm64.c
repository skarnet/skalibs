/* ISC license. */

/* OpenBSD needs that for EOVERFLOW. wtfbsdseriously */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <skalibs/sysdeps.h>
#include <errno.h>
#include <time.h>
#include <skalibs/uint64.h>
#include <skalibs/tai.h>
#include <skalibs/djbtime.h>

int localtm_from_ltm64 (struct tm *l, uint64_t uu, int tzh)
{
  if (uu < TAI_MAGIC) return (errno = EINVAL, 0) ;
  uu -= TAI_MAGIC ;
#if SKALIBS_SIZEOFTIME != 8
  if (uu > 0xFFFFFFFFUL) return (errno = EOVERFLOW, 0) ;
#endif
  {
    time_t u = (time_t)uu ;
    if (tzh & 1 ? !localtime_r(&u, l) : !gmtime_r(&u, l)) return 0 ;
  }
  if (tzh & 2) l->tm_sec++ ;
  return 1 ;
}
