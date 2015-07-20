/* ISC license. */

#include <unistd.h>
#include <errno.h>
#include <skalibs/djbunix.h>

int fd_close (int fd)
{
  for (;;)
  {
    if (!close(fd) || errno == EINPROGRESS) break ;
    if (errno != EINTR) return -1 ;
  }
  return 0 ;
}
