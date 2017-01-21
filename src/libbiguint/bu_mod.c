/* ISC license. */

#include <stdint.h>
#include <skalibs/biguint.h>

int bu_mod (uint32_t *a, unsigned int an, uint32_t const *b, unsigned int bn)
{
  uint32_t q[an] ;
  return bu_div(a, an, b, bn, q, an, a, an) ;
}
