/* ISC license. */

#include <skalibs/tai.h>

int tain_add (tain_t *t, tain_t const *u, tain_t const *v)
{
  t->sec.x = u->sec.x + v->sec.x ;
  t->nano = u->nano + v->nano ;
  if (t->nano > 999999999U)
  {
    t->sec.x++ ;
    t->nano -= 1000000000U ;
  }
  return 1 ;
}
