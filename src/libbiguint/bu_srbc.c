/* ISC license. */

#include <skalibs/biguint.h>

int bu_srbc (uint32_t *a, unsigned int n, int carry)
{
  while (n--)
  {
    int c = a[n] & 1 ;
    a[n] = (a[n] >> 1) | (carry ? 0x80000000U : 0) ;
    carry = c ;
  }
  return carry ;
}
