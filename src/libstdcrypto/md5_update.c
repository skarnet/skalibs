/* ISC license. */

#include <string.h>
#include <skalibs/uint32.h>
#include <skalibs/md5.h>
#include "md5-internal.h"

void md5_update (MD5Schedule *ctx, char const *s, size_t len)
{
  uint32_t t = ctx->bits[0] ;
  if ((ctx->bits[0] = t + (len << 3)) < t)
    ctx->bits[1]++ ;
  ctx->bits[1] += len >> 29 ;
  t = (t >> 3) & 0x3f ;
  if (t)
  {
    unsigned char *p = ctx->in + t ;
    t = 64 - t ;
    if (len < t)
    {
      memcpy(p, s, len) ;
      return ;
    }
    memcpy(p, s, t) ;
    uint32_little_endian((char *)ctx->in, 16) ;
    md5_transform(ctx->buf, (uint32_t *)ctx->in) ;
    s += t ; len -= t ;
  }
  while (len >= 64)
  {
    memcpy(ctx->in, s, 64) ;
    uint32_little_endian((char *)ctx->in, 16) ;
    md5_transform(ctx->buf, (uint32_t *)ctx->in) ;
    s += 64 ; len -= 64 ;
  }
  memcpy(ctx->in, s, len) ;
}
