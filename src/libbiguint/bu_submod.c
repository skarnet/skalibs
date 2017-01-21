/* ISC license. */

#include <stdint.h>
#include <errno.h>
#include <skalibs/biguint.h>

int bu_submod (uint32_t *c, unsigned int cn, uint32_t const *a, unsigned int an, uint32_t const *b, unsigned int bn, uint32_t const *m, unsigned int mn)
{
  if (!bu_sub(c, cn, a, an, b, bn) && bu_add(c, cn, c, cn, m, mn))
    return (errno = EDOM, 0) ;
  return 1 ;
}
