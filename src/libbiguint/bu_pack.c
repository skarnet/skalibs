/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

void bu_pack (char *s, uint32_t const *a, unsigned int n)
{
  while (n--) uint32_pack(s + (n<<2), a[n]) ;
}
