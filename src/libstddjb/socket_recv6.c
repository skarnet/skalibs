/* ISC license. */

#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <skalibs/uint16.h>
#include <skalibs/bytestr.h>
#include <skalibs/ip46.h>
#include <skalibs/socket.h>

#ifdef SKALIBS_IPV6_ENABLED

int socket_recv6 (int s, char *buf, unsigned int len, char *ip6, uint16 *port)
{
  struct sockaddr_in6 sa ;
  socklen_t dummy = sizeof sa ;
  register int r ;
  do r = recvfrom(s, buf, len, 0, (struct sockaddr *)&sa, &dummy) ;
  while ((r == -1) && (errno == EINTR)) ;
  if (r == -1) return -1 ;
  byte_copy(ip6, 16, (char const *)sa.sin6_addr.s6_addr) ;
  uint16_unpack_big((char *)&sa.sin6_port, port) ;
  return r ;
}

#else

int socket_recv6 (int s, char *buf, unsigned int len, char *ip6, uint16 *port)
{
  (void)s ;
  (void)buf ;
  (void)len ;
  (void)ip6 ;
  (void)port ;
  return (errno = ENOSYS, -1) ;
}

#endif
