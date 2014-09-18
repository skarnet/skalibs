/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/bytestr.h>

void uint32_unpack (char const *s, uint32 *u)
{
  uint32 r = T8((unsigned char)s[3]) ; r <<= 8 ;
  r += T8((unsigned char)s[2]) ; r <<= 8 ;
  r += T8((unsigned char)s[1]) ; r <<= 8 ;
  r += T8((unsigned char)s[0]) ;
  *u = r ;
}
