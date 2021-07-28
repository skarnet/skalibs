/* ISC license. */

/* MT-unsafe */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSIGNALFD

#include <errno.h>
#include <signal.h>

#include <skalibs/djbunix.h>
#include <skalibs/selfpipe.h>
#include "selfpipe-internal.h"

void selfpipe_finish (void)
{
  int e = errno ;
  fd_close(selfpipe_fd) ;
  sigprocmask(SIG_UNBLOCK, &selfpipe_caught, 0) ;
  sigemptyset(&selfpipe_caught) ;
  selfpipe_fd = -1 ;
  errno = e ;
}

#else

#include <skalibs/nonposix.h>
#include <skalibs/bsdsnowflake.h>

#include <errno.h>
#include <signal.h>

#include <skalibs/nsig.h>
#include <skalibs/sig.h>
#include <skalibs/djbunix.h>
#include <skalibs/selfpipe.h>
#include "selfpipe-internal.h"

void selfpipe_finish (void)
{
  int e = errno ;
  sigprocmask(SIG_BLOCK, &selfpipe_caught, 0) ;
  sig_restoreto(&selfpipe_caught, SKALIBS_NSIG) ;
  fd_close(selfpipe[1]) ;
  fd_close(selfpipe[0]) ;
  sigprocmask(SIG_UNBLOCK, &selfpipe_caught, 0) ;
  sigemptyset(&selfpipe_caught) ;
  selfpipe[0] = selfpipe[1] = -1 ;
  errno = e ;
}

#endif
