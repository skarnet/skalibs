/* ISC license. */

#include <string.h>
#include <skalibs/uint64.h>

void uint64_reverse (char *s, size_t n)
{
  while (n--)
  {
    uint64_t x ;
    memcpy(&x, s, sizeof(uint64_t)) ;
    x = uint64_bswap(x) ;
    memcpy(s, &x, sizeof(uint64_t)) ;
    s += sizeof(uint64_t) ;
  }
}
