/* ISC license. */

#include <unistd.h>
#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/siovec.h>
#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>

unsigned int openwritevnclose_at (int dirfd, char const *file, siovec_t const *v, unsigned int n)
{
  register unsigned int r ;
  int fd = open_truncatb(dirfd, file) ;
  if (fd < 0) return 0 ;
  r = allwritev(fd, v, n) ;
  if (r < siovec_len(v, n) || fsync(fd) < 0)
  {
    register int e = errno ;
    fd_close(fd) ;
    errno = e ;
    return r ;
  }
  fd_close(fd) ;
  return r ;
}
