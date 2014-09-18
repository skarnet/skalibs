/* ISC license. */

#include <skalibs/uint64.h>
#include <skalibs/tai.h>

void tai_unpack_little (char const *s, tai_t *t)
{
  uint64_unpack(s, &t->x) ;
}
