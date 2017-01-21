/* ISC license. */

#include <stdint.h>
#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

void bu_pack_big (char *s, uint32_t const *a, unsigned int n)
{
  register unsigned int i = 0 ;
  for (; i < n ; i++) uint32_pack_big(s + (i<<2), a[n-1-i]) ;
}
