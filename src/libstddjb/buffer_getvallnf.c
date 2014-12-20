/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/siovec.h>

int buffer_getvallnofill (buffer *b, siovec_t const *v, unsigned int n)
{
  register unsigned int r = buffer_getvnofill(b, v, n) ;
  if (r < siovec_len(v, n))
  {
    buffer_unget(b, r) ;
    return (errno = ENOBUFS, 0) ;
  }
  return 1 ;
}
