/* ISC license. */

#include <sys/types.h>
#include <sys/uio.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/buffer.h>
#include <skalibs/siovec.h>

int buffer_write (int fd, siovec_t const *v, unsigned int n, void *aux)
{
  struct iovec iov[n] ;
  iovec_from_siovec(iov, v, n) ;
  (void)aux ;
  return fd_writev(fd, iov, n) ;
}
