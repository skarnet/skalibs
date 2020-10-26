/* ISC license. */

#include <errno.h>
#include <unistd.h>
#include <skalibs/djbunix.h>

int openwritenclose_unsafe_internal (char const *fn, char const *s, size_t len, dev_t *dev, ino_t *ino, int dosync)
{
  int fd = open_trunccoe(fn) ;
  if (fd < 0) return 0 ;
  if (!writenclose_unsafe_internal(fd, s, len, dev, ino, dosync))
  {
    int e = errno ;
    fd_close(fd) ;
    unlink(fn) ;
    errno = e ;
    return 0 ;
  }
  return 1 ;
}
