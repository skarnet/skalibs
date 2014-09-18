/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/siovec.h>

unsigned int siovec_scatter (siovec_t const *v, unsigned int n, char const *s, unsigned int len)
{
  unsigned int w = 0 ;
  register unsigned int i = 0 ;
  for (; i < n && w < len ; i++)
  {
    register unsigned int chunklen = v[i].len ;
    if (w + chunklen > len) chunklen = len - w ;
    byte_copy(v[i].s, chunklen, s + w) ;
    w += chunklen ;
  }
  return w ;
}
