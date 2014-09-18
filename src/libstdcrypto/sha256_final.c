/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/uint32.h>
#include <skalibs/sha256.h>
#include "sha256-internal.h"

void sha256_final (SHA256Schedule_ref ctx, char *digest)
{
  register unsigned int i = 0 ;
  register unsigned char *p = (unsigned char *)digest ;
  uint32 bits[2] = { ctx->bits[0], ctx->bits[1] } ;

  sha256_feed(ctx, 0x80) ;
  while (ctx->b != 56) sha256_feed(ctx, 0) ;
  sha256_feed(ctx, T8(bits[1]>>24)) ;
  sha256_feed(ctx, T8(bits[1]>>16)) ;
  sha256_feed(ctx, T8(bits[1]>>8)) ;
  sha256_feed(ctx, T8(bits[1])) ;
  sha256_feed(ctx, T8(bits[0]>>24)) ;
  sha256_feed(ctx, T8(bits[0]>>16)) ;
  sha256_feed(ctx, T8(bits[0]>>8)) ;
  sha256_feed(ctx, T8(bits[0])) ;
  for (; i < 8 ; i++)
  {
    *p++ = T8(ctx->buf[i]>>24) ;
    *p++ = T8(ctx->buf[i]>>16) ;
    *p++ = T8(ctx->buf[i]>>8) ;
    *p++ = T8(ctx->buf[i]) ;
  }
}
