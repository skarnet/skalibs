/* ISC license. */

#include <skalibs/biguint.h>

void bu_zero (uint32_t *z, unsigned int n)
{
  while (n--) z[n] = 0 ;
}
