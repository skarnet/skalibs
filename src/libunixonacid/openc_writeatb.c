/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/unix-transactional.h>

int openc_writeatb (int dirfd, char const *name)
{
  int fd = openc_writeat(dirfd, name) ;
  if (fd < 0) return -1 ;
  if (ndelay_off(fd) < 0) return -1 ;
  return fd ;
}
