/* ISC license. */

#include <skalibs/tai.h>

void tain_addsec (tain_t *b, tain_t const *a, int c)
{
  b->nano = a->nano ;
  if (c >= 0)
  {
    tai_t t ;
    tai_u64(&t, c) ;
    tai_add(&b->sec, &a->sec, &t) ;
  }
  else
  {
    tai_t t ;
    tai_u64(&t, -c) ;
    tai_sub(&b->sec, &a->sec, &t) ;
  }
}
