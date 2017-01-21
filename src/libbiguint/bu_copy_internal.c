/* ISC license. */

#include <stdint.h>
#include <skalibs/biguint.h>

void bu_copy_internal (register uint32_t *b, register uint32_t const *a, register unsigned int n)
{
  while (n--) b[n] = a[n] ;
}
