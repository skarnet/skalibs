/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/siovec.h>

unsigned int siovec_seek (siovec_t *v, unsigned int n, unsigned int len)
{
  unsigned int w = 0 ;
  register unsigned int i = 0 ;
  for (; i < n ; i++)
  {
    if (len < v[i].len) break ;
    w += v[i].len ;
    len -= v[i].len ;
    v[i].s = 0 ;
    v[i].len = 0 ;
  }
  if (i < n)
  {
    v[i].s += len ;
    v[i].len -= len ;
    w += len ;
  }
  return w ;
}
