/* ISC license. */

#include <string.h>
#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

size_t bu_fmt (char *s, uint32_t const *x, unsigned int n)
{
  size_t len = 0 ;
  while (n--)
  {
    char fmt[8] ;
    size_t i = uint32_xfmt(fmt, x[n]) ;
    memcpy(s+len, "00000000", 8-i) ;
    memcpy(s+len+8-i, fmt, i) ;
    len += 8 ;
  }
  return len ;
}
