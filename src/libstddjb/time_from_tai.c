 /* ISC license. */

/* OpenBSD needs that for EOVERFLOW. wtfbsdseriously */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <sys/types.h>
#include <errno.h>
#include <skalibs/sysdeps.h>
#include <skalibs/tai.h>

int time_from_tai (time_t *u, tai_t const *t)
{
  register uint64 uu = t->x - TAI_MAGIC ;
#if SKALIBS_SIZEOFTIME < 8
  if ((uu >> 32) && (uu >> 32) != 0xffffffffUL)
    return (errno = EOVERFLOW, 0) ;
#endif
  *u = (time_t)uu ;
  return 1 ;
}
