/* ISC license. */

#include <skalibs/nonposix.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <skalibs/bytestr.h>
#include <skalibs/error.h>
#include <skalibs/webipc.h>

int ipc_recv (int fd, char *s, unsigned int len, char *path)
{
  struct sockaddr_un sa = { .sun_family = AF_UNIX } ;
  socklen_t total = sizeof sa ;
  char tmp[len] ;
  register int r ;
  do r = recvfrom(fd, tmp, len, 0, (struct sockaddr *)&sa, &total) ;
  while ((r == -1) && (errno == EINTR)) ;
  if (r < 0) return r ;
  if (sa.sun_family != AF_UNIX) return (errno = EPROTO, -1) ;
  if (path)
  {
    if (total == sizeof(sa_family_t)) path[0] = 0 ;
    else
    {
      unsigned int l = str_len(sa.sun_path) ;
      if (l > IPCPATH_MAX) return (errno = EPROTO, -1) ;
      byte_copy(path, l+1, sa.sun_path) ;
    }
  }
  byte_copy(s, r, tmp) ;
  return r ;
}
