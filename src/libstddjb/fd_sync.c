/* ISC license. */

#include <unistd.h>
#include <errno.h>
#include <skalibs/djbunix.h>

int fd_sync (int fd)
{
  int r ;
  do
    r = fsync(fd) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
