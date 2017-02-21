/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdint.h>
#include <string.h>
#include <skalibs/uint16.h>
#include <skalibs/socket.h>

int socket_remote4 (int s, char *ip, uint16_t *port)
{
  struct sockaddr_in sa ;
  socklen_t dummy = sizeof sa ;
  if (getpeername(s, (struct sockaddr *)&sa, &dummy) == -1)
    return -1 ;
  memcpy(ip, &sa.sin_addr.s_addr, 4) ;
  uint16_unpack_big((char *)&sa.sin_port, port) ;
  return 0 ;
}
