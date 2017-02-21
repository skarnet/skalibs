/* ISC license. */

#include <errno.h>
#include <skalibs/tai.h>
#include <skalibs/iopause.h>

int iopause_stamp (iopause_fd *x, unsigned int n, tain_t const *deadline, tain_t *stamp)
{
  int r ;
  do
  {
    r = iopause(x, n, deadline, stamp) ;
    if (stamp)
    {
      int e = errno ;
      tain_now(stamp) ;
      errno = e ;
    }
  }
  while ((r < 0) && (errno == EINTR)) ;
  return r ;
}
