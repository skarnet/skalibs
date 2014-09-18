/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <skalibs/uint16.h>
#include <skalibs/socket.h>

int socket_bind4_reuse (int s, char const *ip, uint16 port)
{
  unsigned int opt = 1 ;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt) ;
  return socket_bind4(s, ip, port) ;
}
