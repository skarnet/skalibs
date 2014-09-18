/* ISC license. */

#include <skalibs/tai.h>
#include <skalibs/djbtime.h>

int sysclock_from_localtmn (tain_t *a, localtmn_t const *l)
{
  uint64 u ;
  if (!sysclock_from_localtm(&u, &l->tm)) return 0 ;
  tai_u64(&a->sec, u) ;
  a->nano = l->nano ;
  return 1 ;
}
