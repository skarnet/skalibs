/* ISC license. */

#include <skalibs/ip46.h>

#include <skalibs/fmtscan.h>
#include <skalibs/ip46.h>

unsigned int ip46full_scan (char const *s, ip46full_t_ref ip)
{
  unsigned int len = ip6_scan(s, ip->ip) ;
  if (len) ip->is6 = 1 ;
  else
  {
    len = ip4_scan(s, ip->ip) ;
    if (len) ip->is6 = 0 ;
  }
  return len ;
}
