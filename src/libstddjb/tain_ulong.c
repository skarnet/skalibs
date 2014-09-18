/* ISC license. */

#include <skalibs/tai.h>

void tain_ulong (tain_t *t, unsigned long s)
{
  tai_u64(&t->sec, s) ;
  t->nano = 0 ;
}
