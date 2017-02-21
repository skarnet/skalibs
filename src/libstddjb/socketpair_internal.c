/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <errno.h>
#include <skalibs/djbunix.h>

#ifdef SKALIBS_HASACCEPT4

int socketpair_internal (int domain, int type, int protocol, unsigned int flags, int *sv)
{
  return socketpair(domain, type | ((flags & DJBUNIX_FLAG_NB) ? SOCK_NONBLOCK : 0) | ((flags & DJBUNIX_FLAG_COE) ? SOCK_CLOEXEC : 0), protocol, sv) ;
}

#else

int socketpair_internal (int domain, int type, int protocol, unsigned int flags, int *sv)
{
  int fd[2] ;
  if (socketpair(domain, type, protocol, fd) < 0) return -1 ;
  if (flags & DJBUNIX_FLAG_NB)
  {
    if (ndelay_on(fd[0]) < 0) goto err ;
    if (ndelay_on(fd[1]) < 0) goto err ;
  }
  else
  {
    if (ndelay_off(fd[0]) < 0) goto err ;
    if (ndelay_off(fd[1]) < 0) goto err ;
  }
  if (flags & DJBUNIX_FLAG_COE)
  {
    if (coe(fd[0]) < 0) goto err ;
    if (coe(fd[1]) < 0) goto err ;
  }
  else
  {
    if (uncoe(fd[0]) < 0) goto err ;
    if (uncoe(fd[1]) < 0) goto err ;
  }
  sv[0] = fd[0] ;
  sv[1] = fd[1] ;
  return 0 ;

 err:
  {
    int e = errno ;
    fd_close(fd[1]) ;
    fd_close(fd[0]) ;
    errno = e ;
  }
  return -1 ;
}

#endif
