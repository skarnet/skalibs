/* ISC license. */

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <skalibs/allreadwrite.h>

ssize_t fd_send (int fd, char const *buf, size_t len, unsigned int flags)
{
  register ssize_t r ;
  do r = send(fd, buf, len, (int)flags) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
