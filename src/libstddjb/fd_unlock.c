/* ISC license. */

#include <fcntl.h>
#include <errno.h>

#include <skalibs/djbunix.h>

void fd_unlock (int fd)
{
  struct flock fl =
  {
    .l_type = F_UNLCK,
    .l_whence = SEEK_SET,
    .l_start = 0,
    .l_len = 0
  } ;
  int e = errno ;
  fcntl(fd, F_SETLK, &fl) ;
  errno = e ;
}
