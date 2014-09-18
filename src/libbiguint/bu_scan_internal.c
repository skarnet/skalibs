/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/bytestr.h>
#include <skalibs/biguint.h>

void bu_scan_internal (char const *s, unsigned int len, uint32 *x)
{
  char fmt[9] = "\0\0\0\0\0\0\0\0" ;
  unsigned int i = 0 ;
  if (len & 7)
  {
    byte_copy(fmt, len & 7, s) ;
    uint32_xscan(fmt, x + (len >> 3)) ;
  }
  for (; i < (len >> 3) ; i++)
  {
    byte_copy(fmt, 8, s + len - 8 - (i << 3)) ;
    uint32_xscan(fmt, x + i) ;
  }
}
