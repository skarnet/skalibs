/* ISC license. */

/* MT-unsafe */

#include <skalibs/tai.h>

int tain_setnow (tain_t const *a)
{
  tain_t aa ;
  if (!sysclock_from_tai(&aa.sec.x, &a->sec)) return 0 ;
  aa.nano = a->nano ;
  return sysclock_set(&aa) ;
}
