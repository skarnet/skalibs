/* ISC license. */

#include <sys/types.h>
#include <errno.h>

#include <skalibs/allreadwrite.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

#define N 4096

int slurpn (int fd, stralloc *sa, size_t max)
{
  size_t sabase = sa->len ;
  int wasnull = !sa->s ;
  for (;;)
  {
    ssize_t r ;
    size_t n = max && sa->len - sabase + N > max ? max - (sa->len - sabase) : N ;
    if (!n) { errno = ENOBUFS ; goto err ; }
    if (!stralloc_readyplus(sa, n)) break ;
    r = fd_read(fd, sa->s + sa->len, n) ;
    switch (r)
    {
      case -1 : goto err ;
      case 0 : return 1 ;
      default : sa->len += r ;
    }
  }

err:
  if (wasnull) stralloc_free(sa) ;
  else sa->len = sabase ;
  return 0 ;
}
