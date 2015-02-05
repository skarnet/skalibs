/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/siovec.h>

int buffer_putv (buffer *b, siovec_t const *v, unsigned int n)
{
  unsigned int w = 0 ;
  return buffer_putvall(b, v, n, &w) ? w : -1 ;
}
