/* ISC license. */

#include <skalibs/bitarray.h>

#define B0(n) n, n+1, n+1, n+2
#define B1(n) B0(n), B0(n+1), B0(n+1), B0(n+2)
#define B2(n) B1(n), B1(n+1), B1(n+1), B1(n+2)
#define B3(n) B2(n), B2(n+1), B2(n+1), B2(n+2)

unsigned int bitarray_countones (unsigned char const *c, unsigned int n)
{
  static unsigned char const table[256] = { B3(0) } ;
  unsigned int len = bitarray_div8(n) ;
  unsigned int total = 0 ;
  register unsigned int i = 0 ;
  if (n & 7) len-- ;
  for (; i < len ; i++) total += table[c[i]] ;
  if (n & 7) total += table[c[i] & ((1 << (n & 7)) - 1)] ;
  return total ;
}
