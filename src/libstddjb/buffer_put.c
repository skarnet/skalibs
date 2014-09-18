/* ISC license. */

#include <skalibs/buffer.h>

int buffer_put (buffer *b, char const *s, unsigned int len)
{
  unsigned int w = 0 ;
  if (!buffer_putall(b, s, len, &w)) return -1 ;
  return (int)w ;
}
