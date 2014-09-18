/* ISC license. */

#include <skalibs/uint16.h>
#include <skalibs/bytestr.h>

void uint16_unpack (char const *s, uint16 *u)
{
  uint16 r = T8((unsigned char)s[1]) ; r <<= 8 ;
  r += T8((unsigned char)s[0]) ;
  *u = r ;
}
