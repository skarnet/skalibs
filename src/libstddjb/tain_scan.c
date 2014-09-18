/* ISC license. */

#include <skalibs/fmtscan.h>
#include <skalibs/tai.h>

unsigned int tain_scan (char const *s, tain_t *a)
{
  char pack[TAIN_PACK] ;
  register unsigned int r = ucharn_scan(s, pack, TAIN_PACK) ;
  if (r) tain_unpack(pack, a) ;
  return r ;
}
