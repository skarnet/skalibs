/* ISC license. */

#include <fcntl.h>
#include <skalibs/djbunix.h>

int ndelay_off (int fd)
{
  int got = fcntl(fd, F_GETFL) ;
  return (got == -1) ? -1 : fcntl(fd, F_SETFL, got & ~O_NONBLOCK) ;
}
