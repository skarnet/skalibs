/* ISC license. */

#include <skalibs/djbtime.h>

int tain_from_localtmn (tain_t *a, localtmn_t const *l)
{
  tai_t t ;
  if (!tai_from_localtm(&t, &l->tm)) return 0 ;
  a->sec = t ;
  a->nano = l->nano ;
  return 1 ;
}
