/* ISC license. */

/* MT-unsafe */

#include <skalibs/sysdeps.h>
#include <skalibs/allreadwrite.h>
#include "selfpipe-internal.h"
#include <skalibs/selfpipe.h>

#ifdef SKALIBS_HASSIGNALFD

#include <sys/signalfd.h>

int selfpipe_read (void)
{
  struct signalfd_siginfo buf ;
  register int r = sanitize_read(fd_read(selfpipe_fd, (char *)&buf, sizeof(struct signalfd_siginfo))) ;
  return (r <= 0) ? r : (int)buf.ssi_signo ;
}
      
#else

int selfpipe_read (void)
{
  char c ;
  register int r = sanitize_read((fd_read(selfpipe_fd, &c, 1))) ;
  return (r <= 0) ? r : (int)c ;
}

#endif

