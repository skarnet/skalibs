/* ISC license. */

/* MT-unsafe */

#include <signal.h>

#include <skalibs/sysdeps.h>
#include "selfpipe-internal.h"

sigset_t selfpipe_caught ;

#ifdef SKALIBS_HASSIGNALFD

int selfpipe_fd = -1 ;

#else

#include <unistd.h>

#include <skalibs/allreadwrite.h>

int selfpipe[2] = { -1, -1 } ;

void selfpipe_tophalf (int s)
{
  unsigned char c = (unsigned char)s ;
  write(selfpipe[1], (char *)&c, 1) ;
}

#endif
