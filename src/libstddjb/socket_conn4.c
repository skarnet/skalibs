/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <skalibs/uint16.h>
#include <skalibs/socket.h>

int socket_connect4 (int s, char const *ip, uint16_t port)
{
  struct sockaddr_in sa ;
  int r ;
  memset(&sa, 0, sizeof sa) ;
  sa.sin_family = AF_INET ;
  uint16_big_endian((char *)&port, 1) ;
  sa.sin_port = port ;
  memcpy(&sa.sin_addr.s_addr, ip, 4) ;
  do r = connect(s, (struct sockaddr *)&sa, sizeof sa) ;
  while ((r == -1) && (errno == EINTR)) ;
  if ((r == -1) && (errno == EALREADY)) errno = EINPROGRESS ;
  return r ;
}
