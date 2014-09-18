/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>

unsigned int allreadwrite (iofunc_t_ref op, int fd, register char *buf, register unsigned int len)
{
  register unsigned int written = 0 ;
  while (len)
  {
    register int w = (*op)(fd, buf, len) ;
    if (!w) errno = EPIPE ;
    if (w <= 0) break ;
    written += w ;
    buf += w ;
    len -= w ;
  }
  return written ;
}
