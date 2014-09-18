/* ISC license. */

#include <sys/types.h>
#include <time.h>
#include <skalibs/uint64.h>
#include <skalibs/djbtime.h>

int sysclock_from_localtm (uint64 *uu, struct tm const *l)
{
  uint64 u ;
  if (!ltm64_from_localtm(&u, l)) return 0 ;
  if (!sysclock_from_ltm64(&u)) return 0 ;
  *uu = u ;
  return 1 ;
}
