/* ISC license. */

#include <stdint.h>
#include <skalibs/biguint.h>

int bu_slbc (register uint32_t *a, register unsigned int n, register int carry)
{
  register unsigned int i = 0 ;
  carry = !!carry ;
  for (; i < n ; i++)
  {
    register int c = a[i] >> 31 ;
    a[i] = (a[i] << 1) | carry ;
    carry = c ;
  }
  return carry ;
}
