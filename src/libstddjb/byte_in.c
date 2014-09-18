/* ISC license. */

#include <skalibs/bytestr.h>

unsigned int byte_in (char const *s, register unsigned int n, register char const *sep, register unsigned int len)
{
  register char const *t = s ;
  while (n--)
  {
    if (byte_chr(sep, len, *t) < len) break ;
    ++t ;
  }
  return t - s ;
}
