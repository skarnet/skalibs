/* ISC license. */

#include <sys/types.h>
#include <stdint.h>
#include <skalibs/uint32.h>
#include <skalibs/bytestr.h>
#include <skalibs/biguint.h>

void bu_scan_internal (char const *s, size_t len, uint32_t *x)
{
  char fmt[9] = "\0\0\0\0\0\0\0\0" ;
  size_t i = 0 ;
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
