/* ISC license. */

#include <skalibs/socket.h>

int socket_ioloop_send6 (int fd, char *s, unsigned int len, char *ip, uint16 *port)
{
  return socket_send6(fd, s, len, ip, *port) ;
}
