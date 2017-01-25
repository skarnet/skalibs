/* ISC license. */

#include <skalibs/uint64.h>
#include <skalibs/bytestr.h>

void uint64_pack (char *s, uint64_t u)
{
  ((unsigned char *)s)[0] = T8(u) ; u >>= 8 ;
  ((unsigned char *)s)[1] = T8(u) ; u >>= 8 ;
  ((unsigned char *)s)[2] = T8(u) ; u >>= 8 ;
  ((unsigned char *)s)[3] = T8(u) ; u >>= 8 ;
  ((unsigned char *)s)[4] = T8(u) ; u >>= 8 ;
  ((unsigned char *)s)[5] = T8(u) ; u >>= 8 ;
  ((unsigned char *)s)[6] = T8(u) ; u >>= 8 ;
  ((unsigned char *)s)[7] = T8(u) ;
}
