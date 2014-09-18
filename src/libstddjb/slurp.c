/* ISC license. */

#include <skalibs/allreadwrite.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

#define N 4096

int slurp (stralloc *sa, int fd)
{
  register unsigned int salen = sa->len ;
  for (;;)
  {
    int r ;
    if (!stralloc_readyplus(sa, N)) break ;
    r = fd_read(fd, sa->s + sa->len, N) ;
    switch (r)
    {
      case -1: goto err ;
      case 0:
        stralloc_shrink(sa) ;
        return 1 ;
      default:
        sa->len += r ;
    }
  }
err:
  sa->len = salen ;
  stralloc_shrink(sa) ;
  return 0 ;
}
