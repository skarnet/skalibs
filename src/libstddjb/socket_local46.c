/* ISC license. */

#include <skalibs/nonposix.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <skalibs/uint16.h>
#include <skalibs/bytestr.h>
#include <skalibs/ip46.h>

#ifdef SKALIBS_IPV6_ENABLED

int socket_local46 (int s, ip46_t_ref ip, uint16 *port)
{
  struct sockaddr sa ;
  socklen_t dummy = sizeof sa ;
  if (getsockname(s, &sa, &dummy) < 0) return -1 ;
  if (sa.sa_family == AF_INET6)
  {
    register struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)&sa ;
    byte_copy(ip->ip, 16, sa6->sin6_addr.s6_addr) ;
    uint16_unpack_big((char *)&sa6->sin6_port, port) ;
    ip->is6 = 1 ;
  }
  else if (sa.sa_family == AF_INET)
  {
    register struct sockaddr_in *sa4 = (struct sockaddr_in *)&sa ;
    byte_copy(ip->ip, 4, &sa4->sin_addr.s_addr) ;
    uint16_unpack_big((char *)&sa4->sin_port, port) ;
    ip->is6 = 0 ;
  }
  else return (errno = EAFNOSUPPORT, -1) ;
  return 0 ;
}

#endif
