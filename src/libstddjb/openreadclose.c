/* ISC license. */

#include <errno.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int openreadclose (char const *fn, stralloc *sa, unsigned int bufsize)
{
  int fd = open_readb(fn) ;
  if (fd == -1) return (errno == ENOENT) ? 0 : -1 ;
  if (!slurp(sa, fd))
  {
    register int e = errno ;
    fd_close(fd) ;
    errno = e ;
    return -1 ;
  }
  fd_close(fd) ;
  (void)bufsize ;
  return 0 ;
}
