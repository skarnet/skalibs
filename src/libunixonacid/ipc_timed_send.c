/* ISC license. */

 /* For OpenBSD, that still doesn't know what self-contained headers are */
#include <sys/types.h>

#include <sys/socket.h>
#include <errno.h>
#include <skalibs/error.h>
#include <skalibs/tai.h>
#include <skalibs/iopause.h>
#include <skalibs/unix-timed.h>

 /* For MacOS, that still doesn't know what POSIX says */
#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

int ipc_timed_send (int fd, char const *s, unsigned int len, tain_t const *deadline, tain_t *stamp)
{
  iopause_fd x = { .fd = fd, .events = IOPAUSE_WRITE, .revents = 0 } ;
  for (;;)
  {
    register int r = iopause_stamp(&x, 1, deadline, stamp) ;
    if (r < 0) return 0 ;
    else if (!r) return (errno = ETIMEDOUT, 0) ;
    else if (x.revents & IOPAUSE_WRITE)
    {
      if (send(fd, s, len, MSG_NOSIGNAL) == (int)len) break ;
      if (!error_isagain(errno)) return 0 ;
    }
    else if (x.revents & IOPAUSE_EXCEPT) return (send(fd, s, len, MSG_NOSIGNAL) == (int)len) ;
  }
  return 1 ;
}
