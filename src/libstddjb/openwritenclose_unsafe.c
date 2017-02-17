/* ISC license. */

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/djbunix.h>

int openwritenclose_unsafe_internal (char const *fn, char const *s, size_t len, dev_t *dev, ino_t *ino, int dosync)
{
  struct stat st ;
  int fd = open_trunc(fn) ;
  if (fd < 0) return 0 ;
  if (allwrite(fd, s, len) < len) goto fail ;
  if ((dev || ino) && (fstat(fd, &st) < 0)) goto fail ;
  if (dosync && (fd_sync(fd) < 0) && (errno != EINVAL)) goto fail ;
  fd_close(fd) ;
  if (dev) *dev = st.st_dev ;
  if (ino) *ino = st.st_ino ;
  return 1 ;

 fail:
  {
    int e = errno ;
    fd_close(fd) ;
    unlink(fn) ;
    errno = e ;
  }
  return 0 ;
}
