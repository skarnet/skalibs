/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

void bu_unpack_big (char const *s, uint32 *a, unsigned int n)
{
  register unsigned int i = 0 ;
  for (; i < n ; i++) uint32_unpack_big(s + (i<<2), a + n - 1 - i) ;
}
