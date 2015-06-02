/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/buffer.h>

int buffer_puts (buffer *b, char const *s)
{
  return buffer_put(b, s, str_len(s)) ;
}
