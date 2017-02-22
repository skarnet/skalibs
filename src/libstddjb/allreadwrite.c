/* ISC license. */

#include <sys/types.h>
#include <errno.h>
#include <skalibs/functypes.h>
#include <skalibs/allreadwrite.h>

size_t allreadwrite (iofunc_t_ref op, int fd, char *buf, size_t len)
{
  size_t written = 0 ;
  while (len)
  {
    ssize_t w = (*op)(fd, buf, len) ;
    if (w <= 0)
    {
      if (!w) errno = 0 ;
      break ;
    }
    written += w ;
    buf += w ;
    len -= w ;
  }
  return written ;
}
