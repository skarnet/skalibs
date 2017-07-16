/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/djbunix.h>
#include <skalibs/webipc.h>

int ipc_accept_internal (int s, char *p, size_t l, int *trunc, unsigned int options)
{
  struct sockaddr_un sa ;
  socklen_t dummy = sizeof sa ;
  int fd ;
  memset(&sa, 0, dummy) ;
  do
#ifdef SKALIBS_HASACCEPT4
    fd = accept4(s, (struct sockaddr *)&sa, &dummy, ((options & DJBUNIX_FLAG_NB) ? SOCK_NONBLOCK : 0) | ((options & DJBUNIX_FLAG_COE) ? SOCK_CLOEXEC : 0)) ;
#else
    fd = accept(s, (struct sockaddr *)&sa, &dummy) ;
#endif
  while ((fd == -1) && (errno == EINTR)) ;
  if (fd == -1) return -1 ;
#ifndef SKALIBS_HASACCEPT4
  if ((((options & DJBUNIX_FLAG_NB) ? ndelay_on(fd) : ndelay_off(fd)) < 0)
   || (((options & DJBUNIX_FLAG_COE) ? coe(fd) : uncoe(fd)) < 0))
  {
    fd_close(fd) ;
    return -1 ;
  }
#endif

  if (p)
  {
    dummy = byte_chr(sa.sun_path, dummy, 0) ;
    *trunc = 1 ;
    if (!l) return fd ;
    if (l < (dummy + 1)) dummy = l - 1 ;
    else *trunc = 0 ;
    memcpy(p, sa.sun_path, dummy) ;
    p[dummy] = 0 ;
  }
  return fd ;
}
