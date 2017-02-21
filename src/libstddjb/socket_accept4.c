/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <skalibs/uint16.h>
#include <skalibs/djbunix.h>
#include <skalibs/socket.h>

int socket_accept4_internal (int s, char *ip, uint16_t *port, unsigned int options)
{
  struct sockaddr_in sa ;
  socklen_t dummy = sizeof sa ;
  int fd ;
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
    int e = errno ;
    fd_close(fd) ;
    errno = e ;
    return -1 ;
  }
#endif
  memcpy(ip, &sa.sin_addr.s_addr, 4) ;
  uint16_unpack_big((char *)&sa.sin_port, port) ;
  return fd ;
}
