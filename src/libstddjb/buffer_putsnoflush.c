/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/buffer.h>

int buffer_putsnoflush (buffer *b, char const *s)
{
  return buffer_putnoflush(b, s, str_len(s)) ;
}
