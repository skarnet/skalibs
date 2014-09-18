/* ISC license. */

#include <errno.h>
#include <skalibs/buffer.h>

int buffer_putvallnoflush (buffer *b, siovec_t const *v, unsigned int n)
{
  register unsigned int r = buffer_putvnoflush(b, v, n) ;
  if (r < siovec_len(v, n))
  {
    buffer_unput(b, r) ;
    return (errno = ENOBUFS, 0) ;
  }
  return 1 ;
}
