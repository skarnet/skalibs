/* ISC license. */

#include <stdint.h>
#include <skalibs/uint32.h>
#include <skalibs/bytestr.h>
#include <skalibs/md5.h>
#include "md5-internal.h"

void md5_final (MD5Schedule *ctx, char *digest /* 16 chars */)
{
  unsigned int count = (ctx->bits[0] >> 3) & 0x3F ;
  unsigned char *p = ctx->in + count ;
  *p++ = 0x80;
  count = 63 - count ;
  if (count < 8)
  {
    byte_zero(p, count) ;
    uint32_little_endian((char *)ctx->in, 16) ;
    md5_transform(ctx->buf, (uint32_t *)ctx->in) ;
    byte_zero(ctx->in, 56) ;
  }
  else byte_zero(p, count - 8) ;
  uint32_little_endian((char *)ctx->in, 14) ;

  byte_copy((char *)ctx->in + 56, 4, (char *)&ctx->bits[0]) ;
  byte_copy((char *)ctx->in + 60, 4, (char *)&ctx->bits[1]) ;

  md5_transform(ctx->buf, (uint32_t *)ctx->in) ;
  uint32_little_endian((char *)ctx->buf, 4) ;
  byte_copy(digest, 16, (char *)ctx->buf) ;
}
