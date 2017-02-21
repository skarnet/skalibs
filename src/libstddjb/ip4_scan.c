/* ISC license. */

#include <skalibs/types.h>
#include <skalibs/fmtscan.h>

size_t ip4_scan (char const *s, char *ip)
{
  size_t len = 0 ;
  unsigned int j = 0 ;
  for (; j < 4 ; j++)
  {
    unsigned int u ;
    size_t i = uint_scan(s, &u) ;
    if (!i) return 0 ;
    ip[j] = (char)u ;
    s += i ;
    len += i ;
    if (j == 3) break ;
    if (*s != '.') return 0 ;
    ++s ;
    ++len ;
  }
  return len ;
}
