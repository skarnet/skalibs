/* ISC license. */

#include <skalibs/uint16.h>
#include <skalibs/bytestr.h>

void uint16_pack_big (char *s, uint16_t u)
{
  ((unsigned char *)s)[1] = T8(u) ; u >>= 8 ;
  ((unsigned char *)s)[0] = T8(u) ;
}
