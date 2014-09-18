/* ISC license. */

#include <skalibs/buffer.h>

int buffer_putflush (buffer *b, char const *s, unsigned int len)
{
  int r = buffer_put(b, s, len) ;
  if (r < 0) return -1 ;
  if (!buffer_flush(b)) return -1 ;
  return r ;
}
