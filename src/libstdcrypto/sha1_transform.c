/* ISC license. */

#include <skalibs/uint32.h>
#include "sha1-internal.h"

#define F1(x, y, z) ((x & y) | ((~x) & z))
#define F2(x, y, z) (x ^ y ^ z)
#define F3(x, y, z) ((x & y) | (x & z) | (y & z))
#define F4(x, y, z) (x ^ y ^ z)

#define SHA1STEP(f, data) \
{ \
  register uint32 tmp = e + f(b, c, d) + data + ((a<<5) | (a>>27)); \
  e = d ; \
  d = c ; \
  c = (b<<30) | (b>>2) ; \
  b = a ; \
  a = tmp ; \
}

void sha1_transform (uint32 *buf, uint32 const *in)
{
  register uint32 a = buf[0], b = buf[1], c = buf[2], d = buf[3], e = buf[4] ;
  uint32 w[80] ;
  register unsigned int i = 0 ;

  for (; i < 16 ; i++) w[i] = in[i] ;
  for (; i < 80 ; i++)
  {
    w[i] = w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16] ;
    w[i] = (w[i]<<1) | (w[i]>>31) ;
  }
  for (i = 0 ; i < 20 ; i++)
    SHA1STEP(F1, w[i] + 0x5a827999UL) ;
  for (; i < 40 ; i++)
    SHA1STEP(F2, w[i] + 0x6ed9eba1UL) ;
  for (; i < 60 ; i++)
    SHA1STEP(F3, w[i] + 0x8f1bbcdcUL) ;
  for (; i < 80 ; i++)
    SHA1STEP(F4, w[i] + 0xca62c1d6UL) ;
  buf[0] += a ; buf[1] += b ; buf[2] += c ; buf[3] += d ; buf[4] += e ;
}
