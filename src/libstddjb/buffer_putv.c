/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/diuint.h>
#include <skalibs/siovec.h>

int buffer_putv (buffer *b, siovec_t const *v, unsigned int n)
{
  diuint w = DIUINT_ZERO ;
  if (!buffer_putvall(b, v, n, &w)) return -1 ;
  return (int)(siovec_len(v, w.left) + w.right) ;
}
