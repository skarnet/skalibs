/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/buffer.h>
#include <skalibs/siovec.h>

int buffer_getvall (buffer *b, siovec_t const *v, unsigned int n, unsigned int *written)
{
  unsigned int len = siovec_len(v, n) ;
  siovec_t vv[n] ;
  if (*written > len) return (errno = EINVAL, -1) ;
  {
    register unsigned int i = n ;
    while (i--) vv[i] = v[i] ;
  }
  siovec_seek(vv, n, *written) ;
  for (;;)
  {
    register int r ;
    unsigned int w = buffer_getvnofill(b, vv, n) ;
    *written += w ;
    if (*written >= len) break ;
    siovec_seek(vv, n, w) ;
    r = sanitize_read(buffer_fill(b)) ;
    if (r <= 0) return r ;
  }
  return 1 ;
}

