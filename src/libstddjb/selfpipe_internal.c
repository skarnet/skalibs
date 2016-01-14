/* ISC license. */

/* MT-unsafe */

#include <signal.h>
#include <skalibs/sysdeps.h>
#include "selfpipe-internal.h"

sigset_t selfpipe_caught ;

#ifdef SKALIBS_HASSIGNALFD

int selfpipe_fd = -1 ;

#else

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/djbunix.h>

int selfpipe[2] = { -1, -1 } ;

static void selfpipe_trigger (int s)
{
  unsigned char c = (unsigned char)s ;
  fd_write(selfpipe[1], (char *)&c, 1) ;
}

struct skasigaction const selfpipe_ssa = { &selfpipe_trigger, SKASA_NOCLDSTOP | SKASA_MASKALL } ;

#endif
