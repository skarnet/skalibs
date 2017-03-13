/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <skalibs/uint16.h>
#include <skalibs/socket.h>

ssize_t socket_send4 (int s, char const *buf, size_t len, char const *ip, uint16_t port)
{
  struct sockaddr_in sa ;
  ssize_t r ;
  memset(&sa, 0, sizeof sa) ;
  sa.sin_family = AF_INET ;
  uint16_pack_big((char *)&sa.sin_port, port) ;
  memcpy(&sa.sin_addr, ip, 4) ;
  do r = sendto(s, buf, len, 0, (struct sockaddr *)&sa, sizeof sa) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}
