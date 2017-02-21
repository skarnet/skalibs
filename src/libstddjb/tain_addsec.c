/* ISC license. */

#include <skalibs/uint64.h>
#include <skalibs/tai.h>

int tain_addsec (tain_t *b, tain_t const *a, int c)
{
  if (c >= 0)
  {
    tai_t t = { .x = (uint64_t)c } ;
    tai_add(&b->sec, &a->sec, &t) ;
  }
  else
  {
    tai_t t = { .x = (uint64_t)-c } ;
    tai_sub(&b->sec, &a->sec, &t) ;
  }
  b->nano = a->nano ;
  return 1 ;
}
