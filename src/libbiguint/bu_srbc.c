/* ISC license. */

#include <stdint.h>
#include <skalibs/biguint.h>

int bu_srbc (register uint32_t *a, register unsigned int n, register int carry)
{
  while (n--)
  {
    register int c = a[n] & 1 ;
    a[n] = (a[n] >> 1) | (carry ? 0x80000000U : 0) ;
    carry = c ;
  }
  return carry ;
}
