/* ISC license. */

#include <skalibs/allreadwrite.h>
#include <skalibs/buffer.h>
#include <skalibs/siovec.h>

int buffer_flush1read (int fd, siovec_t const *v, unsigned int n)
{
  if (!buffer_flush(buffer_1)) return -1 ;
  return fd_readsv(fd, v, n) ;
}
