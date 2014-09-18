/* ISC license. */

#include <sys/types.h>
#include <sys/uio.h>
#include <errno.h>
#include <skalibs/allreadwrite.h>

int fd_readv (int fd, struct iovec const *v, unsigned int vlen)
{
  register int r ;
  do r = readv(fd, v, vlen) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
