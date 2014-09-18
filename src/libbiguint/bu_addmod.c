/* ISC license. */

#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

int bu_addmod (uint32 *c, unsigned int cn, uint32 const *a, unsigned int an, uint32 const *b, unsigned int bn, uint32 const *m, unsigned int mn)
{
  if (!bu_add(c, cn, a, an, b, bn)) return 0 ;
  if (bu_cmp(c, cn, m, mn) >= 0) bu_sub(c, cn, c, cn, m, mn) ;
  return 1 ;
}
