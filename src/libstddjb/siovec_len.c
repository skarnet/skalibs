/* ISC license. */

#include <skalibs/siovec.h>

unsigned int siovec_len (siovec_t const *v, register unsigned int n)
{
  register unsigned int w = 0 ;
  while (n--) w += v[n].len ;
  return w ;
}
