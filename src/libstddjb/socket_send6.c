/* ISC license. */

#include <skalibs/nonposix.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <skalibs/uint16.h>
#include <skalibs/bytestr.h>
#include <skalibs/ip46.h>
#include <skalibs/socket.h>

#ifdef SKALIBS_IPV6_ENABLED

int socket_send6 (int s, char const *buf, unsigned int len, char const *ip6, uint16 port)
{
  struct sockaddr_in6 sa ;
  register int r ;
  byte_zero((char *)&sa, sizeof sa) ;
  sa.sin6_family = AF_INET6 ;
  uint16_pack_big((char *)&sa.sin6_port, port) ;
  byte_copy((char *)sa.sin6_addr.s6_addr, 16, ip6) ;
  do r = sendto(s, buf, len, 0, (struct sockaddr *)&sa, sizeof sa) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}

#else

int socket_send6 (int s, char const *buf, unsigned int len, char const *ip6, uint16 port)
{
  (void)s ;
  (void)buf ;
  (void)len ;
  (void)ip6 ;
  (void)port ;
  return (errno = ENOSYS, -1) ;
}

#endif
