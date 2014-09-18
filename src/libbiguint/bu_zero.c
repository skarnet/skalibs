/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

void bu_zero (register uint32 *z, register unsigned int n)
{
  while (n--) z[n] = 0 ;
}
