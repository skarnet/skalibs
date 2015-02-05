/* ISC license. */

#include <skalibs/allreadwrite.h>
#include <skalibs/buffer.h>
#include <skalibs/siovec.h>

int buffer_getv (buffer *b, siovec_t const *v, unsigned int n)
{
  unsigned int w = 0 ;
  register int r = unsanitize_read(buffer_getvall(b, v, n, &w)) ;
  return r <= 0 ? r : w ;
}
