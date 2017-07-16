/* ISC license. */

#include <sys/types.h>
#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/djbunix.h>

static ssize_t readnclose (int fd, char *s, size_t n)
{
  size_t r ;
  errno = 0 ;
  r = allread(fd, s, n) ;
  if (errno)
  {
    fd_close(fd) ;
    return -1 ;
  }
  fd_close(fd) ;
  if (r < n) errno = EPIPE ;
  return r ;
}

ssize_t openreadnclose (char const *file, char *s, size_t n)
{
  int fd = open_readb(file) ;
  return fd < 0 ? fd : readnclose(fd, s, n) ;
}

ssize_t openreadnclose_nb (char const *file, char *s, size_t n)
{
  int fd = open_read(file) ;
  return fd < 0 ? fd : readnclose(fd, s, n) ;
}
