/* ISC license. */

#include <skalibs/tai.h>

void tain_add (tain_t *t, tain_t const *u, tain_t const *v)
{
  tai_add(&t->sec, &u->sec, &v->sec) ;
  t->nano = u->nano + v->nano ;
  if (t->nano > 999999999U)
  {
    t->nano -= 1000000000U ;
    tai_u64(&t->sec, tai_sec(&t->sec)+1) ;
  }
}
