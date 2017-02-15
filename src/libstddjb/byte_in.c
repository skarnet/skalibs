/* ISC license. */

#include <sys/types.h>
#include <skalibs/bytestr.h>

size_t byte_in (char const *s, size_t n, char const *sep, size_t len)
{
  register char const *t = s ;
  while (n--)
  {
    if (byte_chr(sep, len, *t) < len) break ;
    ++t ;
  }
  return t - s ;
}
