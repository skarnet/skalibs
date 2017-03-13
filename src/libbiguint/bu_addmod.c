/* ISC license. */

#include <skalibs/biguint.h>

int bu_addmod (uint32_t *c, unsigned int cn, uint32_t const *a, unsigned int an, uint32_t const *b, unsigned int bn, uint32_t const *m, unsigned int mn)
{
  if (!bu_add(c, cn, a, an, b, bn)) return 0 ;
  if (bu_cmp(c, cn, m, mn) >= 0) bu_sub(c, cn, c, cn, m, mn) ;
  return 1 ;
}
