/* ISC license. */

#include <skalibs/sha256.h>

void sha256_init (SHA256Schedule_ref ctx)
{
  SHA256Schedule empty = SHA256_INIT() ;
  *ctx = empty ;
}
