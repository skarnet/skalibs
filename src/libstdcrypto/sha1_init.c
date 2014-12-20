/* ISC license. */

#include <skalibs/sha1.h>

void sha1_init (SHA1Schedule *ctx)
{
  register unsigned int i = 0 ;
  ctx->buf[0] = 0x67452301UL ;
  ctx->buf[1] = 0xefcdab89UL ;
  ctx->buf[2] = 0x98badcfeUL ;
  ctx->buf[3] = 0x10325476UL ;
  ctx->buf[4] = 0xc3d2e1f0UL ;
  ctx->bits[0] = ctx->bits[1] = 0 ;
  for (; i < 16 ; i++) ctx->in[i] = 0 ;
  ctx->b = 0 ;
}
