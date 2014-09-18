/* ISC license. */

#include <skalibs/tai.h>

void tain_half (tain_t *t, tain_t const *u)
{
  t->nano = u->nano>>1 ;
  if (tai_sec(&u->sec) & 1) t->nano += 500000000U ;
  tai_u64(&t->sec, tai_sec(&u->sec)>>1) ;
}
