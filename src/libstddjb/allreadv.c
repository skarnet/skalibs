/* ISC license. */

#include <skalibs/allreadwrite.h>
#include <skalibs/siovec.h>

unsigned int allreadv (int fd, siovec_t const *v, unsigned int vlen)
{
  return allreadwritev(&fd_readsv, fd, v, vlen) ;
}
