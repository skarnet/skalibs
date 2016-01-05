/* ISC license. */

#include <skalibs/bitarray.h>

unsigned int bitarray_firstclear_skip (register unsigned char const *s, unsigned int max, unsigned int skip)
{
  register unsigned int i = bitarray_div8(skip) ;
  register unsigned int j = i << 3 > max ? max : i << 3 ;
  if (i && s[i-1] != 0xffU)
  {
    while ((skip < j) && bitarray_peek(s, skip)) skip++ ;
    if (skip < j) return skip ;
  }
  return j + bitarray_firstclear(s + i, max - j) ;
}
