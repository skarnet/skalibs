/* ISC license. */

#include <skalibs/tai.h>

int tain_wallclock_read (tain_t *a)
{
  tain_t aa ;
  if (!sysclock_get(&aa)) return 0 ;
  return tain_from_sysclock(a, &aa) ;
}
