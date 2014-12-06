/* ISC license. */

#include <sys/types.h>
#include <sys/uio.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/siovec.h>
#include <skalibs/buffer.h>

int buffer_write (int fd, siovec_t const *v, unsigned int n)
{
  struct iovec iov[n] ;
  iovec_from_siovec(iov, v, n) ;
  return fd_writev(fd, iov, n) ;
}
