/* ISC license. */

#include <skalibs/nonposix.h>

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#include <skalibs/djbunix.h>
#include <skalibs/webipc.h>

int ipc_bind_reuse_lock (int s, char const *p, int *fdlock)
{
  unsigned int opt = 1 ;
  size_t len = strlen(p) ;
  int fd ;
  char lockname[len + 6] ;
  memcpy(lockname, p, len) ;
  memcpy(lockname + len, ".lock", 6) ;
  fd = openc_create(lockname) ;
  if (fd < 0) return -1 ;
  if (lock_exnb(fd) < 0) return -1 ;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt) ;
  unlink(p) ;
  if (ipc_bind(s, p) < 0) return -1 ;
  *fdlock = fd ;
  return 0 ;
}
