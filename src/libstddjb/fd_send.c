/* ISC license. */

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <skalibs/allreadwrite.h>

int fd_send (int fd, char const *buf, unsigned int len, unsigned int flags)
{
  register int r ;
  do r = send(fd, buf, len, (int)flags) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
