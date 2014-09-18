/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int openslurpclose (stralloc *sa, char const *fn)
{
  int r ;
  int e ;
  int fd = open_readb(fn) ;
  if (fd == -1) return 0 ;
  r = slurp(sa, fd) ;
  e = errno ;
  fd_close(fd) ;
  errno = e ;
  return r ;
}
