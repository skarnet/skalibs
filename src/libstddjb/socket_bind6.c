/* ISC license. */

#include <skalibs/nonposix.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <skalibs/uint16.h>
#include <skalibs/bytestr.h>
#include <skalibs/socket.h>
#include <skalibs/ip46.h>

#ifdef SKALIBS_IPV6_ENABLED

int socket_bind6 (int s, char const *ip6, uint16 port)
{
  struct sockaddr_in6 sa ;
  byte_zero(&sa, sizeof sa) ;
  sa.sin6_family = AF_INET6 ;
  uint16_pack_big((char *)&sa.sin6_port, port) ;
  byte_copy(sa.sin6_addr.s6_addr, 16, ip6) ;
  return bind(s, (struct sockaddr *)&sa, sizeof sa) ;
}

#else

int socket_bind6 (int s, char const *ip6, uint16 port)
{
  (void)s ;
  (void)ip6 ;
  (void)port ;
  return (errno = ENOSYS, -1) ;
}

#endif
