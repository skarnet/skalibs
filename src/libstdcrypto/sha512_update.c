/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/sha512.h>
#include "sha512-internal.h"

void sha512_update (SHA512Schedule *ctx, char const *buf, unsigned int len)
{
  register unsigned int pad = ctx->len & 0x7fu ;
  ctx->len += len ;
  if (pad && len >= 128 - pad)
  {
    byte_copy((char *)ctx->buf + pad, 128 - pad, buf) ;
    buf += 128 - pad ; len -= 128 - pad ; pad = 0 ;
    sha512_transform(ctx, ctx->buf) ;
  }

  while (len >= 128)
  {
    sha512_transform(ctx, (unsigned char const *)buf) ;
    buf += 128 ; len -= 128 ;
  }
  byte_copy((char *)ctx->buf + pad, len, buf) ;
}
