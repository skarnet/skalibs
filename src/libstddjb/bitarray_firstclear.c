/* ISC license. */

#include <skalibs/bitarray.h>

unsigned int bitarray_firstclear (register unsigned char const *s, unsigned int max)
{
  unsigned int n = bitarray_div8(max) ;
  register unsigned int i = 0 ;
  for (; i < n ; i++) if (s[i] != 0xffU) break ;
  if (i == n) return max ;
  i <<= 3 ;
  while ((i < max) && bitarray_peek(s, i)) i++ ;
  return i ;
}
