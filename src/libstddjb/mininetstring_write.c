/* ISC license. */

#include <errno.h>
#include <skalibs/uint16.h>
#include <skalibs/uint32.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/mininetstring.h>

int mininetstring_write (int fd, char const *s, uint16 len, uint32 *w)
{
  if (!w)
  {
    char pack[2] ;
    uint16_pack_big(pack, len) ;
    switch (fd_write(fd, pack, 2))
    {
      case -1 : return -1 ;
      case 0 : return (errno = EAGAIN, -1) ;
      case 1 : *w = (1U << 31) ; break ;
      case 2 : *w = len ; break ;
      default : return (errno = EDOM, -1) ;
    }
  }
  if (*w & (1U << 31))
  {
    char c = len & 0xFFU ;
    switch (fd_write(fd, &c, 1))
    {
      case -1 : return -1 ;
      case 0 : return (errno = EAGAIN, -1) ;
      case 1 : *w = len ; break ;
      default : return (errno = EDOM, -1) ;
    }
  }
  *w -= allwrite(fd, s + len - *w, *w) ;
  return *w ? -1 : 1 ;
}
