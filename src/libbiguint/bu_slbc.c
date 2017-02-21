/* ISC license. */

#include <stdint.h>
#include <skalibs/biguint.h>

int bu_slbc (uint32_t *a, unsigned int n, int carry)
{
  unsigned int i = 0 ;
  carry = !!carry ;
  for (; i < n ; i++)
  {
    int c = a[i] >> 31 ;
    a[i] = (a[i] << 1) | carry ;
    carry = c ;
  }
  return carry ;
}
