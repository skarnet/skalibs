/* ISC license. */

#include <sys/types.h>
#include <skalibs/bytestr.h>
#include <skalibs/fmtscan.h>

size_t ip6_scanlist (char *out, size_t max, char const *s, size_t *num)
{
  size_t n = 0, w = 0 ;
  for (; s[w] && (n < max) ; n++)
  {
    char ip[16] ;
    register size_t i = ip6_scan(s + w, ip) ;
    if (!i) break ;
    byte_copy(out + (n << 4), 16, ip) ;
    w += i ;
    while (byte_chr(",; \t\r\n", 6, s[w]) < 6) w++ ;
  }
  *num = n ;
  return w ;
}
