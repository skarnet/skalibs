/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

void bu_copy_internal (register uint32 *b, register uint32 const *a, register unsigned int n)
{
  while (n--) b[n] = a[n] ;
}
