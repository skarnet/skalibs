/* ISC license. */

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <skalibs/allreadwrite.h>

int fd_recv (int fd, char *buf, unsigned int len, unsigned int flags)
{
  register int r ;
  do r = recv(fd, buf, len, (int)flags) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
