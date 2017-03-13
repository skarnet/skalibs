/* ISC license. */

#include <sys/socket.h>
#include <errno.h>
#include <skalibs/error.h>
#include <skalibs/iopause.h>
#include <skalibs/unix-timed.h>

 /* For MacOS, that still doesn't know what POSIX says */
#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

int ipc_timed_send (int fd, char const *s, size_t len, tain_t const *deadline, tain_t *stamp)
{
  iopause_fd x = { .fd = fd, .events = IOPAUSE_WRITE, .revents = 0 } ;
  for (;;)
  {
    int r = iopause_stamp(&x, 1, deadline, stamp) ;
    if (r < 0) return 0 ;
    else if (!r) return (errno = ETIMEDOUT, 0) ;
    else if (x.revents & IOPAUSE_WRITE)
    {
      if (send(fd, s, len, MSG_NOSIGNAL) == (ssize_t)len) break ;
      if (!error_isagain(errno)) return 0 ;
    }
    else if (x.revents & IOPAUSE_EXCEPT) return (send(fd, s, len, MSG_NOSIGNAL) == (ssize_t)len) ;
  }
  return 1 ;
}
