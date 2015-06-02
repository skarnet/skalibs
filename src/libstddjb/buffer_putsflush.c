/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/buffer.h>

int buffer_putsflush (buffer *b, char const *s)
{
  return buffer_putflush(b, s, str_len(s)) ;
}
