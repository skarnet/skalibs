/* ISC license. */

#include <skalibs/iobuffer.h>
#include <skalibs/djbunix.h>

int fd_cat (int from, int to)
{
  iobuffer b ;
  unsigned int n = 0 ;
  if (!iobuffer_init(&b, from, to)) return -1 ;
  for (;;)
  {
    register int r = iobuffer_fill(&b) ;
    if (r < 0) goto err ;
    else if (!r) break ;
    if (!iobuffer_flush(&b)) goto err ;
    n += r ;
  }
  iobuffer_finish(&b) ;
  return n ;

 err:
  iobuffer_finish(&b) ;
  return -1 ;
}
