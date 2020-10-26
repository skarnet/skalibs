/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int openslurpclose (stralloc *sa, char const *fn)
{
  int r ;
  int fd = openbc_read(fn) ;
  if (fd == -1) return 0 ;
  r = slurp(sa, fd) ;
  fd_close(fd) ;
  return r ;
}
