/* ISC license. */

#include <sys/types.h>
#include <string.h>  /* Solaris... */
#include <errno.h>
#include <sys/select.h>
#include <skalibs/tai.h>
#include <skalibs/iopause.h>

int iopause_select (iopause_fd *x, unsigned int len, tain_t const *deadline, tain_t const *stamp)
{
  struct timeval tv = { .tv_sec = 0, .tv_usec = 0 } ;
  int nfds = 0 ;
  fd_set rfds, wfds, xfds ;
  int r ;
  
  FD_ZERO(&rfds) ;
  FD_ZERO(&wfds) ;
  FD_ZERO(&xfds) ;
  if (deadline && tain_less(stamp, deadline))
  {
    tain_t delta ;
    tain_sub(&delta, deadline, stamp) ;
    if (!timeval_from_tain_relative(&tv, &delta))
    {
      if (errno != ERANGE) return -1 ;
      else deadline = 0 ;
    }
  }

  {
    register unsigned int i = 0 ;
    for (; i < len ; i++)
    {
      x[i].revents = 0 ;
      if (x[i].fd >= 0)
      {
        if (x[i].fd >= nfds) nfds = x[i].fd + 1 ;
        if (x[i].events & IOPAUSE_READ) FD_SET(x[i].fd, &rfds) ;
        if (x[i].events & IOPAUSE_WRITE) FD_SET(x[i].fd, &wfds) ;
        if (x[i].events & IOPAUSE_EXCEPT) FD_SET(x[i].fd, &xfds) ;
      }
    }
  }

  r = select(nfds, &rfds, &wfds, &xfds, deadline ? &tv : 0) ;

  if (r > 0)
  {
    register unsigned int i = 0 ;
    for (; i < len ; i++) if (x[i].fd >= 0)
    {
      if ((x[i].events & IOPAUSE_READ) && FD_ISSET(x[i].fd, &rfds))
        x[i].revents |= IOPAUSE_READ ;
      if ((x[i].events & IOPAUSE_WRITE) && FD_ISSET(x[i].fd, &wfds))
        x[i].revents |= IOPAUSE_WRITE ;
      if ((x[i].events & IOPAUSE_EXCEPT) && FD_ISSET(x[i].fd, &xfds))
        x[i].revents |= IOPAUSE_EXCEPT ;
    }
  }

  return r ;
}
