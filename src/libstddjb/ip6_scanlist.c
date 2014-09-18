/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/fmtscan.h>

unsigned int ip6_scanlist (char *out, unsigned int max, char const *s, unsigned int *num)
{
  unsigned int n = 0, w = 0 ;
  for (; s[w] && (n < max) ; n++)
  {
    char ip[16] ;
    register unsigned int i = ip6_scan(s + w, ip) ;
    if (!i) break ;
    byte_copy(out + (n << 4), 16, ip) ;
    w += i ;
    while (byte_chr(",; \t\r\n", 6, s[w]) < 6) w++ ;
  }
  *num = n ;
  return w ;
}
