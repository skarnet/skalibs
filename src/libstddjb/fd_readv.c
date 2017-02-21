/* ISC license. */

#include <sys/uio.h>
#include <errno.h>
#include <skalibs/allreadwrite.h>

ssize_t fd_readv (int fd, struct iovec const *v, unsigned int vlen)
{
  ssize_t r ;
  do r = readv(fd, v, vlen) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
