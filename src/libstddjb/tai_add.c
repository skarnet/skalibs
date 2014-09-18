/* ISC license. */

#include <skalibs/tai.h>

void tai_add (tai_t *t, tai_t const *u, tai_t const *v)
{
  tai_u64(t, tai_sec(u) + tai_sec(v)) ;
}
