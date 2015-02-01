/* ISC license. */

#include <skalibs/allreadwrite.h>
#include <skalibs/siovec.h>

unsigned int allwritev (int fd, siovec_t const *v, unsigned int vlen)
{
  return allreadwritev(&fd_writesv, fd, v, vlen) ;
}
