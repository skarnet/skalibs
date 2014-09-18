/* ISC license. */

#include <skalibs/tai.h>

int tain_less (tain_t const *t, tain_t const *u)
{
  if (tai_sec(&t->sec) < tai_sec(&u->sec)) return 1 ;
  if (tai_sec(&t->sec) > tai_sec(&u->sec)) return 0 ;
  return t->nano < u->nano ;
}
