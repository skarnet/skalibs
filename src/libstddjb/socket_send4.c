/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <skalibs/uint16.h>
#include <skalibs/bytestr.h>
#include <skalibs/socket.h>

int socket_send4 (int s, char const *buf, unsigned int len, char const *ip, uint16 port)
{
  struct sockaddr_in sa ;
  register int r ;
  byte_zero((char *)&sa, sizeof sa) ;
  sa.sin_family = AF_INET ;
  uint16_pack_big((char *)&sa.sin_port, port) ;
  byte_copy((char *)&sa.sin_addr, 4, ip) ;
  do r = sendto(s, buf, len, 0, (struct sockaddr *)&sa, sizeof sa) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
