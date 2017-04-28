/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSIGNALFD

#include <errno.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <skalibs/selfpipe.h>
#include "selfpipe-internal.h"

int selfpipe_trapset (sigset_t const *set)
{
  sigset_t old ;
  if (selfpipe_fd < 0) return (errno = EBADF, -1) ;
  if (sigprocmask(SIG_SETMASK, set, &old) < 0) return -1 ;
  if (signalfd(selfpipe_fd, set, SFD_NONBLOCK | SFD_CLOEXEC) < 0)
  {
    int e = errno ;
    sigprocmask(SIG_SETMASK, &old, 0) ;
    errno = e ;
    return -1 ;
  }
  selfpipe_caught = *set ;
  return 0 ;
}

#else

#include <skalibs/nonposix.h>
#include <errno.h>
#include <signal.h>
#include <skalibs/sig.h>
#include <skalibs/nsig.h>
#include <skalibs/selfpipe.h>
#include "selfpipe-internal.h"

int selfpipe_trapset (sigset_t const *set)
{
  unsigned int i = 1 ;
  if (selfpipe_fd < 0) return (errno = EBADF, -1) ;
  for (; i < SKALIBS_NSIG ; i++)
  {
    int h = sigismember(set, i) ;
    if (h < 0) continue ;
    if (h)
    {
      if (sig_catcha(i, &selfpipe_ssa) < 0) break ;
    }
    else if (sigismember(&selfpipe_caught, i))
    {
      if (sig_restore(i) < 0) break ;
    }
  }
  if (i < SKALIBS_NSIG)
  {
    int e = errno ;
    sig_restoreto(set, i) ;
    errno = e ;
    return -1 ;
  }
  selfpipe_caught = *set ;
  return 0 ;
}

#endif
