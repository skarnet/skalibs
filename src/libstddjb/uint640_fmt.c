/* ISC license. */

#include <skalibs/uint64.h>

unsigned int uint640_fmt_base (char *s, uint64 x, register unsigned int n, unsigned char base)
{
  register unsigned int len = uint64_fmt_base(0, x, base) ;
  while (n-- > len) *s++ = '0' ;
  return uint64_fmt_base(s, x, base) ;
}
