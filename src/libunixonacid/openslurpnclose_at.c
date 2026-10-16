/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>

int openslurpnclose_at (int dirfd, char const *fn, stralloc *sa, size_t n)
{
  int fd = openc_readatb(dirfd, fn) ;
  if (fd < 0) return 0 ;
  if (!slurpn(fd, sa, n))
  {
    fd_close(fd) ;
    return 0 ;
  }
  fd_close(fd) ;
  return 1 ;
}
