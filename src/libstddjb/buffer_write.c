/* ISC license. */

#include <skalibs/allreadwrite.h>
#include <skalibs/siovec.h>
#include <skalibs/buffer.h>

int buffer_write (int fd, siovec_t const *v, unsigned int n)
{
  unsigned int w = allreadwritev(&fd_writesv, fd, v, n) ;
  return w ? (int)w : -1 ;
}
