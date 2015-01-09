/* ISC license. */

#include <skalibs/tai.h>

int tai_sub (tai_t *t, tai_t const *u, tai_t const *v)
{
  return tai_u64(t, tai_sec(u) - tai_sec(v)) ;
}
