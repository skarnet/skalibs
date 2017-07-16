/* ISC license. */

#include <unistd.h>
#include <errno.h>
#include <skalibs/djbunix.h>

void fd_close (int fd)
{
  int e = errno ;
  while (close(fd) < 0 && errno == EINTR) ;
  errno = e ;
}
