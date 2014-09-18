/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <skalibs/uint16.h>
#include <skalibs/bytestr.h>
#include <skalibs/socket.h>

int socket_local4 (int s, char *ip, uint16 *port)
{
  struct sockaddr_in sa ;
  socklen_t dummy = sizeof sa ;

  if (getsockname(s, (struct sockaddr *)&sa, &dummy) == -1)
    return -1 ;
  byte_copy(ip, 4, (char *)&sa.sin_addr.s_addr) ;
  uint16_unpack_big((char *)&sa.sin_port, port) ;
  return 0 ;
}
