/* ISC license. */

#include <skalibs/md5.h>

void md5_init (MD5Schedule_ref ctx)
{
  ctx->buf[0] = 0x67452301UL ;
  ctx->buf[1] = 0xefcdab89UL ;
  ctx->buf[2] = 0x98badcfeUL ;
  ctx->buf[3] = 0x10325476UL ;
  ctx->bits[0] = 0 ;
  ctx->bits[1] = 0 ;
}
