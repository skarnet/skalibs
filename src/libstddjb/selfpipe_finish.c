/* ISC license. */

/* MT-unsafe */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSIGNALFD

#include <signal.h>
#include <skalibs/djbunix.h>
#include "selfpipe-internal.h"
#include <skalibs/selfpipe.h>

void selfpipe_finish (void)
{
  sigprocmask(SIG_UNBLOCK, &selfpipe_caught, 0) ;
  sigemptyset(&selfpipe_caught) ;
  fd_close(selfpipe_fd) ;
  selfpipe_fd = -1 ;
}

#else

#include <skalibs/nonposix.h>
#include <signal.h>
#include <skalibs/sig.h>
#include <skalibs/nsig.h>
#include <skalibs/djbunix.h>
#include "selfpipe-internal.h"
#include <skalibs/selfpipe.h>

void selfpipe_finish (void)
{
  sig_restoreto(&selfpipe_caught, SKALIBS_NSIG-1) ;
  sigemptyset(&selfpipe_caught) ;
  fd_close(selfpipe[1]) ;
  fd_close(selfpipe[0]) ;
  selfpipe[0] = selfpipe[1] = -1 ;
}

#endif
