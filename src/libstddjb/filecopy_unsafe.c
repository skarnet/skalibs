/* ISC license. */

#include <errno.h>
#include <fcntl.h>
#include <skalibs/djbunix.h>

int filecopy_unsafe (char const *src, char const *dst, unsigned int mode)
{
  int d ;
  int s = open2(src, O_RDONLY) ;
  if (s < 0) return 0 ;
  d = open3(dst, O_WRONLY | O_CREAT | O_TRUNC, mode) ;
  if (d < 0)
  {
    register int e = errno ;
    fd_close(s) ;
    errno = e ;
    return 0 ;
  }
  if (fd_cat(s, d) < 0)
  {
    register int e = errno ;
    fd_close(d) ;
    fd_close(s) ;
    errno = e ;
    return 0 ;
  }
  fd_close(d) ;
  fd_close(s) ;
  return 1 ;
}

