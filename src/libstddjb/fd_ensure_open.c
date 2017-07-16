/* ISC license. */

#include <errno.h>
#include <fcntl.h>
#include <skalibs/djbunix.h>

int fd_ensure_open (int fd, int w)
{
  int dummy ;
  if (fcntl(fd, F_GETFD, &dummy) < 0)
  {
    int newfd ;
    if (errno != EBADF) return 0 ;
    newfd = open2("/dev/null", w ? O_WRONLY : O_RDONLY) ;
    if (newfd < 0) return 0 ;
    if (fd_move(fd, newfd) < 0)
    {
      fd_close(newfd) ;
      return 0 ;
    }
  }
  return 1 ;
}
