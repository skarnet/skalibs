/* ISC license. */

#include <skalibs/sha256.h>
#include "sha256-internal.h"

void sha256_update (SHA256Schedule *ctx, char const *buf, size_t len)
{
  size_t i = 0 ;
  for (; i < len ; i++) sha256_feed(ctx, (unsigned char)buf[i]) ;
}
