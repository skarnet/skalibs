/* ISC license. */

#include <stdint.h>
#include <skalibs/uint32.h>

uint32_t uint32_bswap (uint32_t a)
{
  return
   (a & 0x000000ffu) << 24 |
   (a & 0x0000ff00u) << 8 |
   (a & 0x00ff0000u) >> 8 |
   (a & 0xff000000u) >> 24 ;
}
