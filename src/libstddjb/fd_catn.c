/* ISC license. */

#include <sys/types.h>
#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/iobuffer.h>
#include <skalibs/djbunix.h>

size_t fd_catn (int from, int to, size_t n)
{
  size_t w = 0 ;
  if (n >= IOBUFFER_SIZE)
  {
    iobuffer b ;
    if (!iobuffer_init(&b, from, to)) return 0 ;
    while (n >= IOBUFFER_SIZE)
    {
      register ssize_t r = iobuffer_fill(&b) ;
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
    size_t r = allread(from, buf, n) ;
    size_t v = 0 ;
    if (r) v = allwrite(to, buf, r) ;
    w += v ;
  }
  return w ;
}
