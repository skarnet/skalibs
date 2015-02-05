/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/siovec.h>

int buffer_putvall (buffer *b, siovec_t const *v, unsigned int n, unsigned int *written)
{
  unsigned int len = siovec_len(v, n) ;
  unsigned int w = n ;
  siovec_t vv[n] ;
  if (*written > len) return (errno = EINVAL, 0) ;
  while (w--) vv[w] = v[w] ;
  w = *written ;
  for (;;)
  {
    siovec_seek(vv, n, w) ;
    w = buffer_putvnoflush(b, vv, n) ;
    *written += w ;
    if (*written >= len) return 1 ;
    buffer_flush(b) ;
    if (buffer_isfull(b)) return 0 ;
  }
}
