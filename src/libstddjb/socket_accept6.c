/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <skalibs/uint16.h>
#include <skalibs/bytestr.h>
#include <skalibs/djbunix.h>
#include <skalibs/ip46.h>
#include <skalibs/socket.h>

#ifdef SKALIBS_IPV6_ENABLED

int socket_accept6_internal (int s, char *ip6, uint16 *port, unsigned int options)
{
  struct sockaddr_in6 sa ;
  socklen_t dummy = sizeof sa ;
  register int fd ;
  do
#ifdef SKALIBS_HASACCEPT4
    fd = accept4(s, (struct sockaddr *)&sa, &dummy, ((options & DJBUNIX_FLAG_NB) ? SOCK_NONBLOCK : 0) | ((options & DJBUNIX_FLAG_COE) ? SOCK_CLOEXEC : 0)) ;
#else
    fd = accept(s, (struct sockaddr *)&sa, &dummy) ;
#endif
  while ((fd < 0) && (errno == EINTR)) ;
  if (fd < 0) return -1 ;
#ifndef SKALIBS_HASACCEPT4
  if ((((options & DJBUNIX_FLAG_NB) ? ndelay_on(fd) : ndelay_off(fd)) < 0)
   || (((options & DJBUNIX_FLAG_COE) ? coe(fd) : uncoe(fd)) < 0))
  {
    register int e = errno ;
    fd_close(fd) ;
    errno = e ;
    return -1 ;
  }
#endif
  byte_copy(ip6, 16, (char const *)sa.sin6_addr.s6_addr) ;
  uint16_unpack_big((char *)&sa.sin6_port, port) ;
  return fd ;
}

#else

int socket_accept6_internal (int s, char *ip6, uint16 *port, unsigned int options)
{
  (void)s ;
  (void)ip6 ;
  (void)port ;
  (void)options ;
  return (errno = ENOSYS, -1) ;
}

#endif
