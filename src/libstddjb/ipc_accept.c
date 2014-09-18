/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <skalibs/bytestr.h>
#include <skalibs/djbunix.h>
#include <skalibs/webipc.h>

int ipc_accept_internal (int s, char *p, unsigned int l, int *trunc, unsigned int options)
{
  struct sockaddr_un sa ;
  socklen_t dummy = sizeof sa ;
  register int fd ;
  byte_zero((char*)&sa, (unsigned int)dummy) ;
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
    register int e = errno ;
    fd_close(fd) ;
    errno = e ;
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
    byte_copy(p, dummy, sa.sun_path) ;
    p[dummy] = 0 ;
  }
  return fd ;
}
