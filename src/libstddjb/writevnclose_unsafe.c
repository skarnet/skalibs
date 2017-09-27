/* ISC license. */

#include <sys/uio.h>
#include <sys/stat.h>
#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/siovec.h>
#include <skalibs/djbunix.h>

int writevnclose_unsafe_internal (int fd, struct iovec const *v, unsigned int vlen, dev_t *dev, ino_t *ino, int dosync)
{
  struct stat st ;
  if (allwritev(fd, v, vlen) < siovec_len(v, vlen)) return 0 ;
  if ((dev || ino) && (fstat(fd, &st) < 0)) return 0 ;
  if (dosync && (fd_sync(fd) < 0) && (errno != EINVAL)) return 0 ;
  fd_close(fd) ;
  if (dev) *dev = st.st_dev ;
  if (ino) *ino = st.st_ino ;
  return 1 ;
}
