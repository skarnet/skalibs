/* ISC license. */

#include <string.h>
#include <skalibs/uint32.h>
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
    memset(p, 0, count) ;
    uint32_little_endian((char *)ctx->in, 16) ;
    md5_transform(ctx->buf, (uint32_t *)ctx->in) ;
    memset(ctx->in, 0, 56) ;
  }
  else memset(p, 0, count - 8) ;
  uint32_little_endian((char *)ctx->in, 14) ;

  memcpy(ctx->in + 56, &ctx->bits[0], 4) ;
  memcpy(ctx->in + 60, &ctx->bits[1], 4) ;

  md5_transform(ctx->buf, (uint32_t *)ctx->in) ;
  uint32_little_endian((char *)ctx->buf, 4) ;
  memcpy(digest, ctx->buf, 16) ;
}
