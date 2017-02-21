/* ISC license. */

#include <stdint.h>
#include <string.h>
#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

void bu_scan_internal (char const *s, size_t len, uint32_t *x)
{
  char fmt[9] = "\0\0\0\0\0\0\0\0" ;
  size_t i = 0 ;
  if (len & 7)
  {
    memcpy(fmt, s, len & 7) ;
    uint32_xscan(fmt, x + (len >> 3)) ;
  }
  for (; i < (len >> 3) ; i++)
  {
    memcpy(fmt, s + len - 8 - (i << 3), 8) ;
    uint32_xscan(fmt, x + i) ;
  }
}
