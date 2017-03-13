/* ISC license. */

#include <skalibs/nonposix.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <skalibs/uint16.h>
#include <skalibs/ip46.h>

#ifdef SKALIBS_IPV6_ENABLED

int socket_remote46 (int s, ip46_t *ip, uint16_t *port)
{
  struct sockaddr sa ;
  socklen_t dummy = sizeof sa ;
  if (getpeername(s, &sa, &dummy) < 0) return -1 ;
  if (sa.sa_family == AF_INET6)
  {
    struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)&sa ;
    memcpy(ip->ip, sa6->sin6_addr.s6_addr, 16) ;
    uint16_unpack_big((char *)&sa6->sin6_port, port) ;
    ip->is6 = 1 ;
  }
  else if (sa.sa_family == AF_INET)
  {
    struct sockaddr_in *sa4 = (struct sockaddr_in *)&sa ;
    memcpy(ip->ip, &sa4->sin_addr.s_addr, 4) ;
    uint16_unpack_big((char *)&sa4->sin_port, port) ;
    ip->is6 = 0 ;
  }
  else return (errno = EAFNOSUPPORT, -1) ;
  return 0 ;
}

#endif
