/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/siovec.h>

unsigned int siovec_bytein (siovec_t const *v, unsigned int n, char const *sep, unsigned int seplen)
{
  unsigned int w = 0 ;
  unsigned int i = 0 ;
  for (; i < n ; i++)
  {
    register unsigned int pos = byte_in(v[i].s, v[i].len, sep, seplen) ;
    w += pos ;
    if (pos < v[i].len) break ;
  }
  return w ;
}
