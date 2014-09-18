/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <skalibs/uint16.h>
#include <skalibs/bytestr.h>
#include <skalibs/socket.h>

int socket_recv4 (int s, char *buf, unsigned int len, char *ip, uint16 *port)
{
  struct sockaddr_in sa ;
  socklen_t dummy = sizeof sa ;
  register int r ;
  do r = recvfrom(s, buf, len, 0, (struct sockaddr *)&sa, &dummy) ;
  while ((r == -1) && (errno == EINTR)) ;
  if (r == -1) return -1 ;
  byte_copy(ip, 4, (char *)&sa.sin_addr) ;
  uint16_unpack_big((char *)&sa.sin_port, port) ;
  return r ;
}
