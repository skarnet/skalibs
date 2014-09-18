/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/siovec.h>

int buffer_putvflush (buffer *b, siovec_t const *v, unsigned int n)
{
  int r = buffer_putv(b, v, n) ;
  if (r < 0) return -1 ;
  if (!buffer_flush(b)) return -1 ;
  return r ;
}
