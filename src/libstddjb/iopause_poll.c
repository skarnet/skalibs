/* ISC license. */

#include <errno.h>
#include <poll.h>
#include <skalibs/tai.h>
#include <skalibs/iopause.h>

int iopause_poll (iopause_fd *x, unsigned int len, tain_t const *deadline, tain_t const *stamp)
{
  int millisecs = 0 ;
  if (!deadline) millisecs = -1 ;
  else if (tain_less(stamp, deadline))
  {
    tain_t t ;
    tain_sub(&t, deadline, stamp) ;
    millisecs = tain_to_millisecs(&t) ;
  }
  return poll(x, len, millisecs) ;
}
