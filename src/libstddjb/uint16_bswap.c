/* ISC license. */

#include <stdint.h>
#include <skalibs/uint16.h>

uint16_t uint16_bswap (uint16_t a)
{
  return (a & 0x00ffu) << 8 | (a & 0xff00u) >> 8 ;
}
