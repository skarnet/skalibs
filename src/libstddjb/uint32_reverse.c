/* ISC license. */

#include <stdint.h>
#include <string.h>
#include <skalibs/uint32.h>

void uint32_reverse (char *s, size_t n)
{
  while (n--)
  {
    uint32_t x ;
    memcpy(&x, s, sizeof(uint32_t)) ;
    x = uint32_bswap(x) ;
    memcpy(s, &x, sizeof(uint32_t)) ;
    s += sizeof(uint32_t) ;
  }
}
