/* ISC license. */

#include <skalibs/buffer.h>
#include <skalibs/genwrite.h>

int genwrite_put_buffer (void *target, char const *s, unsigned int len)
{
  register buffer *b = target ;
  return buffer_put(b, s, len) ;
}
