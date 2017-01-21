/* ISC license. */

#include <stdint.h>
#include <skalibs/biguint.h>

void bu_zero (register uint32_t *z, register unsigned int n)
{
  while (n--) z[n] = 0 ;
}
