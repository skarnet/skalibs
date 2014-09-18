/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/iobuffer.h>
#include <skalibs/djbunix.h>

unsigned int fd_catn (int from, int to, unsigned int n)
{
  unsigned int w = 0 ;
  if (n >= IOBUFFER_SIZE)
  {
    iobuffer b ;
    if (!iobuffer_init(&b, from, to)) return 0 ;
    while (n >= IOBUFFER_SIZE)
    {
      register int r = iobuffer_fill(&b) ;
      if (r <= 0)
      {
        iobuffer_finish(&b) ;
        if (!r) errno = EPIPE ;
        return w ;
      }
      if (!iobuffer_flush(&b))
      {
        iobuffer_finish(&b) ;
        return w ;
      }
      n -= r ; w += r ;
    }
    iobuffer_finish(&b) ;
  }

  {
    char buf[n] ;
    unsigned int r = allread(from, buf, n) ;
    unsigned int v = 0 ;
    if (r) v = allwrite(to, buf, r) ;
    w += v ;
  }
  return w ;
}
