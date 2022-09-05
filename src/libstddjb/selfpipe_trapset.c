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
  if (selfpipe_fd < 0) return (errno = EBADF, 0) ;
  if (sigprocmask(SIG_SETMASK, set, &old) < 0) return 0 ;
  if (signalfd(selfpipe_fd, set, SFD_NONBLOCK | SFD_CLOEXEC) < 0)
  {
    int e = errno ;
    sigprocmask(SIG_SETMASK, &old, 0) ;
    errno = e ;
    return 0 ;
  }
  selfpipe_caught = *set ;
  return 1 ;
}

#else

#include <skalibs/nonposix.h>

#include <errno.h>
#include <signal.h>

#include <skalibs/nsig.h>
#include <skalibs/sig.h>
#include <skalibs/selfpipe.h>
#include "selfpipe-internal.h"

int selfpipe_trapset (sigset_t const *set)
{
  unsigned int i = 1 ;
  if (selfpipe_fd < 0) return (errno = EBADF, 0) ;
  for (; i < SKALIBS_NSIG ; i++)
  {
    int h = sigismember(set, i) ;
    if (h < 0) continue ;
    if (h)
    {
      if (!sig_catch(i, &selfpipe_tophalf)) goto err ;
    }
    else if (sigismember(&selfpipe_caught, i))
    {
      if (!sig_restore(i)) goto err ;
    }
  }
  sig_blocknone() ;
  selfpipe_caught = *set ;
  return 1 ;

 err:
  {
    int e = errno ;
    sig_restoreto(set, i) ;
    errno = e ;
  }
  return 0 ;
}

#endif
