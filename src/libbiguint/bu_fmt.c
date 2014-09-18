/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/bytestr.h>
#include <skalibs/biguint.h>

unsigned int bu_fmt (char *s, uint32 const *x, unsigned int n)
{
  unsigned int len = 0 ;
  while (n--)
  {
    char fmt[8] ;
    unsigned int i = uint32_xfmt(fmt, x[n]) ;
    byte_copy(s+len, 8-i, "00000000") ;
    byte_copy(s+len+8-i, i, fmt) ;
    len += 8 ;
  }
  return len ;
}
