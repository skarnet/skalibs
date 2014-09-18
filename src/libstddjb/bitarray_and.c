/* ISC license. */

#include <skalibs/bitarray.h>

void bitarray_and (unsigned char *c, unsigned char const *a, unsigned char const *b, unsigned int n)
{
  unsigned int len = bitarray_div8(n) ;
  register unsigned int i = 0 ;
  for (; i < len ; i++) c[i] = a[i] & b[i] ;
}
