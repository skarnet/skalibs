/* ISC license. */

#include <sys/types.h>
#include <sys/uio.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/siovec.h>

int fd_writesv (int fd, siovec_t const *v, unsigned int vlen)
{
  struct iovec vv[vlen] ;
  iovec_from_siovec(vv, v, vlen) ;
  return fd_writev(fd, vv, vlen) ;
}
