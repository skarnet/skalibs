/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/djbunix.h>

static int readnclose (int fd, char *s, unsigned int n)
{
  register int r = allread(fd, s, n) ;
  register int e = errno ;
  fd_close(fd) ;
  if ((r > 0) && (r < (int)n)) e = EPIPE ;
  errno = e ;
  return r ;
}

int openreadnclose (char const *file, char *s, unsigned int n)
{
  register int fd = open_readb(file) ;
  return fd < 0 ? fd : readnclose(fd, s, n) ;
}

int openreadnclose_nb (char const *file, char *s, unsigned int n)
{
  register int fd = open_read(file) ;
  return fd < 0 ? fd : readnclose(fd, s, n) ;
}
