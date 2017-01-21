/* ISC license. */

#include <skalibs/md5.h>

void md5_init (MD5Schedule *ctx)
{
  ctx->buf[0] = 0x67452301U ;
  ctx->buf[1] = 0xefcdab89U ;
  ctx->buf[2] = 0x98badcfeU ;
  ctx->buf[3] = 0x10325476U ;
  ctx->bits[0] = 0 ;
  ctx->bits[1] = 0 ;
}
