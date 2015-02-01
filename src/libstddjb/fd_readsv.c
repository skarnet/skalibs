/* ISC license. */

#include <skalibs/allreadwrite.h>
#include <skalibs/siovec.h>

int fd_readsv (int fd, siovec_t const *v, unsigned int vlen)
{
  struct iovec vv[vlen] ;
  iovec_from_siovec(vv, v, vlen) ;
  return fd_readv(fd, vv, vlen) ;
}
