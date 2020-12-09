/* ISC license. */

#include <skalibs/nonposix.h>

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>

#include <skalibs/djbunix.h>
#include <skalibs/socket.h>

int ipc_bind_reuse_lock (int s, char const *p, int *fdlock)
{
  unsigned int opt = 1 ;
  size_t len = strlen(p) ;
  int fd ;
  int r ;
  char lockname[len + 6] ;
  memcpy(lockname, p, len) ;
  memcpy(lockname + len, ".lock", 6) ;
  fd = openc_create(lockname) ;
  if (fd < 0) return -1 ;
  r = fd_lock(fd, 1, 1) ;
  if (r < 0) return -1 ;
  if (!r) return (errno = EBUSY, -1) ;
  r = errno ;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt) ;
  errno = r ;
  unlink_void(p) ;
  if (ipc_bind(s, p) < 0) return -1 ;
  *fdlock = fd ;
  return 0 ;
}
