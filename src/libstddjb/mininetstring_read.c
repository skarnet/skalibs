/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/uint32.h>
#include <skalibs/stralloc.h>
#include <skalibs/mininetstring.h>

int mininetstring_read (int fd, stralloc *sa, uint32 *w)
{
  if (!*w)
  {
    char pack[2] ;
    switch (fd_read(fd, pack, 2))
    {
      case -1 : return -1 ;
      case 0 : return 0 ;
      case 1 : *w = ((uint32)pack[0] << 8) | (1U << 31) ; break ;
      case 2 : *w = ((uint32)pack[0] << 8) | (uint32)pack[1] | (1U << 30) ; break ;
      default : return (errno = EDOM, -1) ;
    }
  }
  if (*w & (1U << 31))
  {
    char c ;
    switch (fd_read(fd, &c, 1))
    {
      case -1 : return -1 ;
      case 0 : return (errno = EPIPE, -1) ;
      case 1 : *w |= (uint32)c | (1U << 30) ; *w &= ~(1U << 31) ; break ;
      default : return (errno = EDOM, -1) ;
    }
  }
  if (*w & (1U << 30))
  {
    if (!stralloc_readyplus(sa, *w & ~(1U << 30))) return -1 ;
    *w &= ~(1U << 30) ;
  }
  {
    register unsigned int r = allread(fd, sa->s + sa->len, *w) ;
    sa->len += r ; *w -= r ;
  }
  return *w ? -1 : 1 ;
}
