/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/buffer.h>

int buffer_putsallflush (buffer *b, char const *s, unsigned int *w)
{
  return buffer_putallflush(b, s, str_len(s), w) ;
}
