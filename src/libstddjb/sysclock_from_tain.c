 /* ISC license. */

#include <skalibs/tai.h>

int sysclock_from_tain (tain_t *u, tain_t const *t)
{
  if (!sysclock_from_tai(&u->sec.x, &t->sec)) return 0 ;
  u->nano = t->nano ;
  return 1 ;
}
