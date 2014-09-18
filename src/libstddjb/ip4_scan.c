/* ISC license. */

#include <skalibs/uint.h>

unsigned int ip4_scan (char const *s, char *ip)
{
  register unsigned int j = 0 ;
  unsigned int len = 0 ;
  for (; j < 4 ; j++)
  {
    unsigned int u ;
    register unsigned int i = uint_scan(s, &u) ;
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
