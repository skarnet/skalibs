/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/siovec.h>

unsigned int siovec_bytechr (siovec_t const *v, unsigned int n, char c)
{
  unsigned int w = 0 ;
  unsigned int i = 0 ;
  for (; i < n ; i++)
  {
    register unsigned int pos = byte_chr(v[i].s, v[i].len, c) ;
    w += pos ;
    if (pos < v[i].len) break ;
  }
  return w ;
}
