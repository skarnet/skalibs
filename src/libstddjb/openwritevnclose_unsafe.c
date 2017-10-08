/* ISC license. */

#include <sys/uio.h>
#include <errno.h>
#include <unistd.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/djbunix.h>

int openwritevnclose_unsafe_internal (char const *fn, struct iovec const *v, unsigned int vlen, dev_t *dev, ino_t *ino, int dosync)
{
  int fd = open_trunc(fn) ;
  if (fd < 0) return 0 ;
  if (!writevnclose_unsafe_internal(fd, v, vlen, dev, ino, dosync))
  {
    int e = errno ;
    fd_close(fd) ;
    unlink(fn) ;
    errno = e ;
    return 0 ;
  }
  return 1 ;
}
