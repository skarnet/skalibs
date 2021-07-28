/* ISC license. */

/* MT-unsafe */

#include <errno.h>
#include <signal.h>

#include <skalibs/sysdeps.h>
#include <skalibs/selfpipe.h>
#include "selfpipe-internal.h"

#ifdef SKALIBS_HASSIGNALFD

#include <sys/signalfd.h>

int selfpipe_trap (int sig)
{
  sigset_t ss = selfpipe_caught ;
  sigset_t old ;
  if (selfpipe_fd < 0) return (errno = EBADF, 0) ;
  if ((sigaddset(&ss, sig) < 0) || (sigprocmask(SIG_BLOCK, &ss, &old) < 0)) return 0 ;
  if (signalfd(selfpipe_fd, &ss, SFD_NONBLOCK | SFD_CLOEXEC) < 0)
  {
    int e = errno ;
    sigprocmask(SIG_SETMASK, &old, 0) ;
    errno = e ;
    return 0 ;
  }
  selfpipe_caught = ss ;
  return 1 ;
}

#else

#include <skalibs/sig.h>

int selfpipe_trap (int sig)
{
  sigset_t set ;
  if (selfpipe_fd < 0) return (errno = EBADF, 0) ;
  if (!sig_catch(sig, &selfpipe_tophalf)) return 0 ;
  sigaddset(&selfpipe_caught, sig) ;
  sig_unblock(sig) ;
  return 1 ;
}

#endif
