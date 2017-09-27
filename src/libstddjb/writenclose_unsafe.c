/* ISC license. */

#include <sys/stat.h>
#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/djbunix.h>

int writenclose_unsafe_internal (int fd, char const *s, size_t len, dev_t *dev, ino_t *ino, int dosync)
{
  struct stat st ;
  if (allwrite(fd, s, len) < len) return 0 ;
  if ((dev || ino) && (fstat(fd, &st) < 0)) return 0 ;
  if (dosync && (fd_sync(fd) < 0) && (errno != EINVAL)) return 0 ;
  fd_close(fd) ;
  if (dev) *dev = st.st_dev ;
  if (ino) *ino = st.st_ino ;
  return 1 ;
}
