/* ISC license. */

#include <stdint.h>
#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

void bu_unpack (char const *s, uint32_t *a, register unsigned int n)
{
  while (n--) uint32_unpack(s + (n<<2), a + n) ;
}
