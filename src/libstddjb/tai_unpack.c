/* ISC license. */

#include <skalibs/uint64.h>
#include <skalibs/tai.h>

void tai_unpack (char const *s, tai_t *t)
{
  uint64_unpack_big(s, &t->x) ;
}
