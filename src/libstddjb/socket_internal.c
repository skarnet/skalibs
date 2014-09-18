/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <errno.h>
#include <skalibs/djbunix.h>

#ifdef SKALIBS_HASACCEPT4

int socket_internal (int domain, int type, int protocol, unsigned int flags)
{
  return socket(domain, type | ((flags & DJBUNIX_FLAG_NB) ? SOCK_NONBLOCK : 0) | ((flags & DJBUNIX_FLAG_COE) ? SOCK_CLOEXEC : 0), protocol) ;
}

#else

int socket_internal (int domain, int type, int protocol, unsigned int flags)
{
  int s = socket(domain, type, protocol) ;
  if (s == -1) return -1 ;
  if ((((flags & DJBUNIX_FLAG_NB) ? ndelay_on(s) : ndelay_off(s)) < 0)
   || (((flags & DJBUNIX_FLAG_COE) ? coe(s) : uncoe(s)) < 0))
  {
    register int e = errno ;
    fd_close(s) ;
    errno = e ;
    return -1 ;
  }
  return s ;
}

#endif
