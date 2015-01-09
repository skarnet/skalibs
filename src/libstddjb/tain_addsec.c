/* ISC license. */

#include <skalibs/tai.h>

int tain_addsec (tain_t *b, tain_t const *a, int c)
{
  if (c >= 0)
  {
    tai_t t ;
    if (!tai_u64(&t, c)) return 0 ;
    if (!tai_add(&b->sec, &a->sec, &t)) return 0 ;
  }
  else
  {
    tai_t t ;
    if (!tai_u64(&t, -c)) return 0 ;
    if (!tai_sub(&b->sec, &a->sec, &t)) return 0 ;
  }
  b->nano = a->nano ;
  return 1 ;
}
