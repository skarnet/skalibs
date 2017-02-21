/* ISC license. */

#include <sys/types.h>
#include <skalibs/fmtscan.h>
#include <skalibs/tai.h>

size_t tain_fmt (char *s, tain_t const *a)
{
  char pack[TAIN_PACK] ;
  tain_pack(pack, a) ;
  return ucharn_fmt(s, pack, TAIN_PACK) ;
}
