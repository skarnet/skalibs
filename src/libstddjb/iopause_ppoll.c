/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASPPOLL

#define _GNU_SOURCE
#include <errno.h>
#include <time.h>
#include <poll.h>
#include <skalibs/tai.h>
#include <skalibs/iopause.h>

int iopause_ppoll (iopause_fd *x, unsigned int len, tain_t const *deadline, tain_t const *stamp)
{
  struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 } ;
  if (deadline && tain_less(stamp, deadline))
  {
    tain_t delta ;
    tain_sub(&delta, deadline, stamp) ;
    if (!timespec_from_tain_relative(&ts, &delta))
    {
      if (errno != ERANGE) return -1 ;
      else deadline = 0 ;
    }
  }
  return ppoll(x, len, deadline ? &ts : 0, 0) ;
}

#else

#include <errno.h>
#include <skalibs/iopause.h>

int iopause_ppoll (iopause_fd *x, unsigned int len, tain_t const *deadline, tain_t const *stamp)
{
  (void)x ;
  (void)len ;
  (void)deadline ;
  (void)stamp ;
  return (errno = ENOSYS, -1) ;
}

#endif
