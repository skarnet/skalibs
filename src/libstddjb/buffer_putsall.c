/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/buffer.h>

int buffer_putsall (buffer *b, char const *s, unsigned int *w)
{
  return buffer_putall(b, s, str_len(s), w) ;
}
