/* ISC license. */

#include <sys/types.h>
#include <stdint.h>
#include <skalibs/uint32.h>
#include <skalibs/bytestr.h>
#include <skalibs/biguint.h>

size_t bu_fmt (char *s, uint32_t const *x, unsigned int n)
{
  size_t len = 0 ;
  while (n--)
  {
    char fmt[8] ;
    size_t i = uint32_xfmt(fmt, x[n]) ;
    byte_copy(s+len, 8-i, "00000000") ;
    byte_copy(s+len+8-i, i, fmt) ;
    len += 8 ;
  }
  return len ;
}
