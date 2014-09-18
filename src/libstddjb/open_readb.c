/* ISC license. */

#include <skalibs/djbunix.h>

int open_readb (char const *fn)
{
  register int fd = open_read(fn) ;
  if (fd == -1) return -1 ;
  if (ndelay_off(fd) == -1)
  {
    fd_close(fd) ;
    return -1 ;
  }
  return fd ;
}
