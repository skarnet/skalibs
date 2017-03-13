/* ISC license. */

#include <skalibs/biguint.h>

void bu_copy_internal (uint32_t *b, uint32_t const *a, unsigned int n)
{
  while (n--) b[n] = a[n] ;
}
