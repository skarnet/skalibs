/* ISC license. */

#include <sys/types.h>
#include <skalibs/iobuffer.h>
#include <skalibs/djbunix.h>

int fd_cat (int from, int to)
{
  iobuffer b ;
  size_t n = 0 ;
  if (!iobuffer_init(&b, from, to)) return -1 ;
  for (;;)
  {
    ssize_t r = iobuffer_fill(&b) ;
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
