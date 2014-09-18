/* ISC license. */

#include <errno.h>
#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

int bu_submod (uint32 *c, unsigned int cn, uint32 const *a, unsigned int an, uint32 const *b, unsigned int bn, uint32 const *m, unsigned int mn)
{
  if (!bu_sub(c, cn, a, an, b, bn) && bu_add(c, cn, c, cn, m, mn))
    return (errno = EDOM, 0) ;
  return (errno = 0, 1) ;
}
