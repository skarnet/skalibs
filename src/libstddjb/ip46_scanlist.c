/* ISC license. */

#include <sys/types.h>
#include <skalibs/ip46.h>
#include <skalibs/bytestr.h>
#include <skalibs/fmtscan.h>

size_t ip46full_scanlist (ip46full_t *out, size_t max, char const *s, size_t *num)
{
  size_t n = 0, w = 0 ;
  for (; s[w] && (n < max) ; n++)
  {
    ip46full_t z ;
    register size_t i = ip6_scan(s + w, z.ip) ;
    if (i) z.is6 = 1 ;
    else
    {
      i = ip4_scan(s + w, z.ip) ;
      if (!i) break ;
      z.is6 = 0 ;
    }
    out[n] = z ;
    w += i ;
    while (byte_chr(",; \t\r\n", 6, s[w]) < 6) w++ ;
  }
  *num = n ;
  return w ;
}
