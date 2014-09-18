/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/fmtscan.h>

unsigned int ip4_scanu32 (char const *s, uint32 *ip)
{
  char pack[4] ;
  register unsigned int r = ip4_scan(s, pack) ;
  if (r) uint32_unpack_big(pack, ip) ;
  return r ;
}
