/* ISC license. */

#include <skalibs/nonposix.h>

#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#include <skalibs/webipc.h>
#include <skalibs/posixishard.h>

ssize_t ipc_recv (int fd, char *s, size_t len, char *path)
{
  struct sockaddr_un sa = { .sun_family = AF_UNIX } ;
  socklen_t total = sizeof sa ;
  char tmp[len] ;
  ssize_t r ;
  do r = recvfrom(fd, tmp, len, 0, (struct sockaddr *)&sa, &total) ;
  while ((r == -1) && (errno == EINTR)) ;
  if (r < 0) return r ;
  if (sa.sun_family != AF_UNIX) return (errno = EPROTO, -1) ;
  if (path)
  {
    if (total == sizeof(sa_family_t)) path[0] = 0 ;
    else
    {
      size_t l = strlen(sa.sun_path) ;
      if (l > IPCPATH_MAX) return (errno = EPROTO, -1) ;
      memcpy(path, sa.sun_path, l+1) ;
    }
  }
  memcpy(s, tmp, r) ;
  return r ;
}
