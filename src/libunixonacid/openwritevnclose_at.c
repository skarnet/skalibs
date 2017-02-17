/* ISC license. */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/siovec.h>
#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>

size_t openwritevnclose_at (int dirfd, char const *file, struct iovec const *v, unsigned int n)
{
  size_t r ;
  int fd = open_truncatb(dirfd, file) ;
  if (fd < 0) return 0 ;
  r = allwritev(fd, v, n) ;
  if (r < siovec_len(v, n) || fsync(fd) < 0)
  {
    int e = errno ;
    fd_close(fd) ;
    errno = e ;
    return r ;
  }
  fd_close(fd) ;
  return r ;
}
