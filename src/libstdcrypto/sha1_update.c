/* ISC license. */

#include <skalibs/sha1.h>
#include "sha1-internal.h"

void sha1_update (SHA1Schedule_ref ctx, char const *buf, unsigned int len)
{
  register unsigned int i = 0 ;
  for (; i < len ; i++) sha1_feed(ctx, (unsigned char)buf[i]) ;
}
