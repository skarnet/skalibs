/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/siovec.h>

unsigned int siovec_trunc (siovec_t *v, unsigned int n, unsigned int len)
{
  register unsigned int i = siovec_len(v, n) ;
  if (i < len) return n ;
  len = i - len ;
  i = n ;
  while (len && i--)
  {
    register unsigned int w = len > v[i].len ? v[i].len : len ;
    v[i].len -= w ; len -= w ;
  }
  return i ;
}
