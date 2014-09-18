/* ISC license. */

/* MT-unsafe */

#include <errno.h>
#include <signal.h>
#include <skalibs/sysdeps.h>
#include "selfpipe-internal.h"
#include <skalibs/selfpipe.h>

#ifdef SKALIBS_HASSIGNALFD
#include <sys/signalfd.h>
#else
#include <skalibs/djbunix.h>
#endif

int selfpipe_init (void)
{
  if (selfpipe_fd >= 0) return (errno = EBUSY, -1) ;
  sigemptyset(&selfpipe_caught) ;
#ifdef SKALIBS_HASSIGNALFD
  selfpipe_fd = signalfd(-1, &selfpipe_caught, SFD_NONBLOCK | SFD_CLOEXEC) ;
#else
  if (pipenbcoe(selfpipe) < 0) return -1 ;
#endif
  return selfpipe_fd ;
}
