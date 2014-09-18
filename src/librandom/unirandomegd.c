/* ISC license. */

#include <errno.h>
#include <skalibs/djbunix.h>
#include <skalibs/randomegd.h>
#include <skalibs/unirandom.h>
#include <skalibs/unirandomegd.h>

int unirandomegd_sinit (union unirandominfo *u, char const *path)
{
  register int s = randomegd_open(path) ;
  if (s == -1) return 0 ;
  if (coe(s) == -1)
  {
    register int e = errno ;
    fd_close(s) ;
    errno = e ;
    return 0 ;
  }
  u->egd.fd = s ;
  return 1 ;
}

int unirandomegd_finish (union unirandominfo *u)
{
  return !fd_close(u->egd.fd) ;
}

unsigned int unirandomegd_readb (union unirandominfo *u, char *s, unsigned int n)
{
  return randomegd_readb(u->egd.fd, s, n) ;
}

unsigned int unirandomegd_readnb (union unirandominfo *u, char *s, unsigned int n)
{
  return randomegd_readnb(u->egd.fd, s, n) ;
}
