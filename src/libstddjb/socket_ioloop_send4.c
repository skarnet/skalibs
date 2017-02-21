/* ISC license. */

#include <sys/types.h>
#include <stdint.h>
#include <skalibs/socket.h>

ssize_t socket_ioloop_send4 (int fd, char *s, size_t len, char *ip, uint16_t *port)
{
  return socket_send4(fd, s, len, ip, *port) ;
}
