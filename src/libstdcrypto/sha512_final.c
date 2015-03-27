/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/uint64.h>
#include <skalibs/sha512.h>
#include "sha512-internal.h"

void sha512_final (SHA512Schedule *ctx, char *digest)
{
  register unsigned int i = 0 ;
  register unsigned int pad = ctx->len % 128;

  ctx->buf[pad++] = 0x80 ;
  if (pad > 112)
  {
    byte_zero(ctx->buf + pad, 128 - pad) ;
    sha512_transform(ctx, ctx->buf) ;
    pad = 0 ;
  }
  byte_zero(ctx + pad, 120 - pad) ;
  uint64_pack_big((char *)ctx->buf + 120, ctx->len << 3) ;
  sha512_transform(ctx, ctx->buf) ;

  for (; i < 8 ; i++) uint64_pack_big(digest + (i << 3), ctx->h[i]) ;
}
