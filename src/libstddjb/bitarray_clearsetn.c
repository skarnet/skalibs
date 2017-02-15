/* ISC license. */

#include <sys/types.h>
#include <skalibs/bitarray.h>

void bitarray_clearsetn (register unsigned char *s, register size_t a, register size_t b, register int h)
{
  if (!b) return ;
  b += a ;
  if ((a >> 3) == ((b-1) >> 3))
  {
    register unsigned char mask = (1 << (a & 7)) - 1 ^ (1 << 1 + (b-1 & 7)) - 1 ;
    if (h) s[a>>3] |= mask ; else s[a>>3] &= ~mask ;
  }
  else
  {
    register unsigned char mask = ~((1 << (a & 7)) - 1) ;
    register size_t i = (a>>3) + 1 ;
    if (h) s[a>>3] |= mask ; else s[a>>3] &= ~mask ;
    mask = h ? 0xff : 0x00 ;
    for (; i < b>>3 ; i++) s[i] = mask ;
    mask = (1 << (b & 7)) - 1 ;
    if (h) s[b>>3] |= mask ; else s[b>>3] &= ~mask ;
  }
}
