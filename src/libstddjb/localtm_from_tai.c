/* ISC license. */

#include <time.h>
#include <skalibs/uint64.h>
#include <skalibs/tai.h>
#include <skalibs/djbtime.h>

int localtm_from_tai (struct tm *l, tai_t const *t, int tz)
{
  uint64_t u ;
  if (!ltm64_from_tai(&u, t)) return 0 ;
  return localtm_from_ltm64(l, u, tz) ;
}
