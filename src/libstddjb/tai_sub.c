/* ISC license. */

#include <skalibs/tai.h>

int tai_sub (tai_t *t, tai_t const *u, tai_t const *v)
{
  t->x = u->x - v->x ;
  return 1 ;
}
