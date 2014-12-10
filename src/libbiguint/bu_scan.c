/* ISC license. */

/* OpenBSD needs that for EOVERFLOW. wtfbsdseriously */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <errno.h>
#include <skalibs/uint32.h>
#include <skalibs/bitarray.h>
#include <skalibs/biguint.h>

int bu_scan (char const *s, unsigned int len, uint32 *x, unsigned int xn, unsigned int zeron)
{
  register unsigned int n = bitarray_div8(zeron) ;
  if (xn < n) return (errno = EOVERFLOW, 0) ;
  bu_scan_internal(s, len, x) ;
  bu_zero(x + n, xn - n) ;
  return 1 ;
}
