/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <skalibs/uint16.h>
#include <skalibs/djbunix.h>
#include <skalibs/socket.h>

int socket_accept4_internal (int s, char *ip, uint16_t *port, unsigned int options)
{
  int fd ;
  struct sockaddr_in sa ;
  socklen_t dummy = sizeof sa ;
  do
#ifdef SKALIBS_HASACCEPT4
    fd = accept4(s, (struct sockaddr *)&sa, &dummy, ((options & O_NONBLOCK) ? SOCK_NONBLOCK : 0) | ((options & O_CLOEXEC) ? SOCK_CLOEXEC : 0)) ;
#else
    fd = accept(s, (struct sockaddr *)&sa, &dummy) ;
#endif
  while ((fd < 0) && (errno == EINTR)) ;
  if (fd < 0) return -1 ;
#ifndef SKALIBS_HASACCEPT4
  if ((((options & O_NONBLOCK) ? ndelay_on(fd) : ndelay_off(fd)) < 0)
   || (((options & O_CLOEXEC) ? coe(fd) : uncoe(fd)) < 0))
  {
    fd_close(fd) ;
    return -1 ;
  }
#endif
  memcpy(ip, &sa.sin_addr.s_addr, 4) ;
  *port = uint16_big(sa.sin_port) ;
  return fd ;
}
