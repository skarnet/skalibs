/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/bytestr.h>
#include <skalibs/fmtscan.h>

unsigned int ip4_scanlist_u32 (uint32 *out, unsigned int max, char const *s, unsigned int *num)
{
  unsigned int n = 0, w = 0 ;
  for (; s[w] && (n < max) ; n++)
  {
    register unsigned int i = ip4_scanu32(s + w, out + n) ;
    if (!i) break ;
    w += i ;
    while (byte_chr(",:; \t\r\n", 7, s[w]) < 7) w++ ;
  }
  *num = n ;
  return w ;
}
