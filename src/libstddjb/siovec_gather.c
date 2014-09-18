/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/siovec.h>

unsigned int siovec_gather (siovec_t const *v, unsigned int n, char *s, unsigned int max)
{
  unsigned int w = 0 ;
  register unsigned int i = 0 ;
  for (; i < n && w < max ; i++)
  {
    register unsigned int len = v[i].len ;
    if ((w + len) > max) len = max - w ;
    byte_copy(s + w, len, v[i].s) ;
    w += len ;
  }
  return w ;
}
