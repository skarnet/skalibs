/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <skalibs/uint16.h>
#include <skalibs/bytestr.h>
#include <skalibs/socket.h>

int socket_bind4 (int s, char const *ip, uint16 port)
{
  struct sockaddr_in sa ;
  byte_zero(&sa, sizeof sa) ;
  sa.sin_family = AF_INET ;
  uint16_big_endian((char *)&port, 1) ;
  sa.sin_port = port ;
  byte_copy((char *)&sa.sin_addr.s_addr, 4, ip) ;
  return bind(s, (struct sockaddr *)&sa, sizeof sa) ;
}
