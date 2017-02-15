/* ISC license. */

#include <sys/types.h>
#include <skalibs/bitarray.h>

int bitarray_testandpoke (register unsigned char *s, register size_t n, register int h)
{
  register unsigned char mask = 1 << (n & 7) ;
  register unsigned char c = s[n>>3] ;
  s[n>>3] = h ? c | mask : c & ~mask ;
  return (c & mask) ? 1 : 0 ;
}
