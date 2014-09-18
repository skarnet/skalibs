/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/fmtscan.h>

unsigned int ip4_scanlist (char *out, unsigned int max, char const *s, unsigned int *num)
{
  unsigned int n = 0, w = 0 ;
  for (; s[w] && (n < max) ; n++)
  {
    register unsigned int i = ip4_scan(s + w, out + (n << 2)) ;
    if (!i) break ;
    w += i ;
    while (byte_chr(",:; \t\r\n", 7, s[w]) < 7) w++ ;
  }
  *num = n ;
  return w ;
}
