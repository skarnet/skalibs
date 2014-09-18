/* ISC license. */

#include <skalibs/tai.h>

void tain_sub (tain_t *t, tain_t const *u, tain_t const *v)
{
  tain_t uu = *u ;
  tai_sub(&t->sec, &uu.sec, &v->sec) ;
  t->nano = uu.nano - v->nano ;
  if (t->nano > uu.nano)
  {
    t->nano += 1000000000U ;
    tai_u64(&t->sec, tai_sec(&t->sec)-1) ;
  }
}
