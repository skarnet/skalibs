/* ISC license. */

#include <skalibs/tai.h>

int tain_sysclock (tain_t *a)
{
  tain_t aa ;
  if (!sysclock_get(&aa)) return 0 ;
  if (!tai_from_sysclock(&a->sec, aa.sec.x)) return 0 ;
  a->nano = aa.nano ;
  return 1 ;
}
