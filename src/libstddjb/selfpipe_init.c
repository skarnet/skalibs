/* ISC license. */

/* MT-unsafe */

#include <signal.h>

#include <skalibs/sysdeps.h>
#include <skalibs/sig.h>
#include <skalibs/selfpipe.h>
#include "selfpipe-internal.h"

#ifdef SKALIBS_HASSIGNALFD

#include <sys/signalfd.h>

int selfpipe_init (void)
{
  sigemptyset(&selfpipe_caught) ;
  selfpipe_fd = signalfd(selfpipe_fd, &selfpipe_caught, SFD_NONBLOCK | SFD_CLOEXEC) ;
  sig_blocknone() ;
  return selfpipe_fd ;
}

#else

#include <skalibs/djbunix.h>

int selfpipe_init (void)
{
  if (selfpipe_fd >= 0) selfpipe_finish() ;
  sigemptyset(&selfpipe_caught) ;
  sig_blocknone() ;
  return pipenbcoe(selfpipe) < 0 ? -1 : selfpipe_fd ;
}

#endif
