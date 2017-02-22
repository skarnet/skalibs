/* ISC license. */

#include <sys/types.h>
#include <skalibs/bitarray.h>

void bitarray_not (unsigned char *s, size_t a, size_t b)
{
  if (!b) return ;
  b += a ;
  if ((a >> 3) == ((b-1) >> 3))
    s[a>>3] ^= ((1 << (a & 7)) - 1) ^ ((a << (b & 7)) - 1) ;
  else
  {
    size_t i = (a>>3) + 1 ;
    s[a>>3] ^= ~((1 << (a & 7)) - 1) ;
    for (; i < (b>>3) ; i++) s[i] = ~s[i] ;
    s[b>>3] ^= (1 << (b & 7)) - 1 ;
  }
}
