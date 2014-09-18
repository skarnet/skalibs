/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <skalibs/uint16.h>
#include <skalibs/bytestr.h>
#include <skalibs/socket.h>

int socket_connect4 (int s, char const *ip, uint16 port)
{
  struct sockaddr_in sa ;
  register int r ;
  byte_zero(&sa, sizeof sa) ;
  sa.sin_family = AF_INET ;
  uint16_big_endian((char *)&port, 1) ;
  sa.sin_port = port ;
  byte_copy(&sa.sin_addr.s_addr, 4, ip) ;
  do r = connect(s, (struct sockaddr *)&sa, sizeof sa) ;
  while ((r == -1) && (errno == EINTR)) ;
  if ((r == -1) && (errno == EALREADY)) errno = EINPROGRESS ;
  return r ;
}
