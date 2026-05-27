/* ISC license. */

#include <errno.h>

#include <skalibs/tai.h>
#include <skalibs/iopause.h>

int iopause_stamp (iopause_fd *x, unsigned int n, tain const *deadline, tain *stamp)
{
  int e = errno ;
  for (;;)
  {
    int r = iopause(x, n, deadline, stamp) ;
    if (r == -1)
    {
      if (errno != EINTR) return -1 ;
      if (stamp) tain_now(stamp) ;
    }
    else
    {
      if (stamp) tain_now(stamp) ;
      errno = e ;
      if (r > 0) return r ;
      if (deadline && stamp && !tain_less(stamp, deadline)) return 0 ;
    }
  }
}
