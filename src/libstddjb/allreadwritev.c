/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/siovec.h>

unsigned int allreadwritev (iovfunc_t_ref op, int fd, siovec_t const *v, unsigned int vlen)
{
  register unsigned int written = 0 ;
  siovec_t vv[vlen] ;
  for (; written < vlen ; written++) vv[written] = v[written] ;
  written = 0 ;
  while (siovec_len(vv, vlen))
  {
    register int w = (*op)(fd, vv, vlen) ;
    if (w <= 0) break ;
    w = siovec_seek(vv, vlen, w) ;
    written += w ;
  }
  return written ;
}
