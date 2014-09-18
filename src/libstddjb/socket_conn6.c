/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <skalibs/uint16.h>
#include <skalibs/bytestr.h>
#include <skalibs/socket.h>
#include <skalibs/ip46.h>

#ifdef SKALIBS_IPV6_ENABLED

int socket_connect6 (int s, char const *ip6, uint16 port)
{
  struct sockaddr_in6 sa ;
  register int r ;
  byte_zero(&sa, sizeof sa) ;
  sa.sin6_family = AF_INET6 ;
  uint16_pack_big((char *)&sa.sin6_port,port) ;
  byte_copy(sa.sin6_addr.s6_addr, 16, ip6) ;
  do r = connect(s, (struct sockaddr *)&sa, sizeof sa) ;
  while ((r == -1) && (errno == EINTR)) ;
  if ((r == -1) && (errno == EALREADY)) errno = EINPROGRESS ;
  return r ;
}

#else

int socket_connect6 (int s, char const *ip6, uint16 port)
{
  (void)s ;
  (void)ip6 ;
  (void)port ;
  return (errno = ENOSYS, -1) ;
}

#endif
