/* ISC license. */

#include <stdint.h>
#include <skalibs/uint32.h>
#include <skalibs/bytestr.h>

void uint32_unpack_big (char const *s, uint32_t *u)
{
  uint32_t r = T8((unsigned char)s[0]) ; r <<= 8 ;
  r += T8((unsigned char)s[1]) ; r <<= 8 ;
  r += T8((unsigned char)s[2]) ; r <<= 8 ;
  r += T8((unsigned char)s[3]) ;
  *u = r ;
}
