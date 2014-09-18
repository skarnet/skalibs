/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/djbunix.h>

int openreadnclose (char const *file, char *s, unsigned int n)
{
  register int r ;
  int fd = open_readb(file) ;
  if (fd == -1) return -1 ;
  r = allread(fd, s, n) ;
  if (r == -1)
  {
    fd_close(fd) ;
    return -1 ;
  }
  fd_close(fd) ;
  if ((r > 0) && (r < (int)n)) errno = EPIPE ;
  return r ;
}
