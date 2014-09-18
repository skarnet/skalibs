/* ISC license. */

#include <skalibs/uint32.h>
#include "sha256-internal.h"

#define F1(x, y, z) ((x & y) | ((~x) & z))
#define F2(x, y, z) ((x & y) | (x & z) | (y & z))

#define ROTR(x,n) (((x)>>(n)) | ((x)<<(32-(n))))
#define CAPITALSIGMA0(x) (ROTR(x,2)^ROTR(x,13)^ROTR(x,22))
#define CAPITALSIGMA1(x) (ROTR(x,6)^ROTR(x,11)^ROTR(x,25))
#define SMALLSIGMA0(x) (ROTR(x,7)^ROTR(x,18)^((x)>>3))
#define SMALLSIGMA1(x) (ROTR(x,17)^ROTR(x,19)^((x)>>10))

static uint32 const sha256_constants[64] =
{
  0x428a2f98UL, 0x71374491UL, 0xb5c0fbcfUL, 0xe9b5dba5UL,
  0x3956c25bUL, 0x59f111f1UL, 0x923f82a4UL, 0xab1c5ed5UL,
  0xd807aa98UL, 0x12835b01UL, 0x243185beUL, 0x550c7dc3UL,
  0x72be5d74UL, 0x80deb1feUL, 0x9bdc06a7UL, 0xc19bf174UL,
  0xe49b69c1UL, 0xefbe4786UL, 0x0fc19dc6UL, 0x240ca1ccUL,
  0x2de92c6fUL, 0x4a7484aaUL, 0x5cb0a9dcUL, 0x76f988daUL,
  0x983e5152UL, 0xa831c66dUL, 0xb00327c8UL, 0xbf597fc7UL,
  0xc6e00bf3UL, 0xd5a79147UL, 0x06ca6351UL, 0x14292967UL,
  0x27b70a85UL, 0x2e1b2138UL, 0x4d2c6dfcUL, 0x53380d13UL,
  0x650a7354UL, 0x766a0abbUL, 0x81c2c92eUL, 0x92722c85UL,
  0xa2bfe8a1UL, 0xa81a664bUL, 0xc24b8b70UL, 0xc76c51a3UL,
  0xd192e819UL, 0xd6990624UL, 0xf40e3585UL, 0x106aa070UL,
  0x19a4c116UL, 0x1e376c08UL, 0x2748774cUL, 0x34b0bcb5UL,
  0x391c0cb3UL, 0x4ed8aa4aUL, 0x5b9cca4fUL, 0x682e6ff3UL,
  0x748f82eeUL, 0x78a5636fUL, 0x84c87814UL, 0x8cc70208UL,
  0x90befffaUL, 0xa4506cebUL, 0xbef9a3f7UL, 0xc67178f2UL
} ;

void sha256_transform (uint32 *buf, uint32 const *in)
{
  uint32 w[64] ;
  unsigned int i = 0 ;
  register uint32 a = buf[0], b = buf[1], c = buf[2], d = buf[3], e = buf[4], f = buf[5], g = buf[6], h = buf[7] ;

  for (; i < 16 ; i++) w[i] = in[i] ;
  for (; i < 64 ; i++)
    w[i] = SMALLSIGMA1(w[i-2]) + w[i-7] + SMALLSIGMA0(w[i-15]) + w[i-16] ;
  for (i = 0 ; i < 64 ; i++)
  {
    uint32 temp1 = h + CAPITALSIGMA1(e) + F1(e, f, g) + sha256_constants[i] + w[i] ;
    uint32 temp2 = CAPITALSIGMA0(a) + F2(a, b, c) ;
    h = g ; g = f ; f = e ; e = d + temp1 ;
    d = c ; c = b ; b = a ; a = temp1 + temp2 ;
  }
  buf[0] += a ; buf[1] += b ; buf[2] += c ; buf[3] += d ;
  buf[4] += e ; buf[5] += f ; buf[6] += g ; buf[7] += h ;
}
