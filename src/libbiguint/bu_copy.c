/* ISC license. */

/* OpenBSD needs that for EOVERFLOW. wtfbsdseriously */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <stdint.h>
#include <errno.h>
#include <skalibs/biguint.h>

int bu_copy (uint32_t *b, unsigned int bn, uint32_t const *a, unsigned int an)
{
  unsigned int alen = bu_len(a, an) ;
  if (bn < alen)
  {
    bu_copy_internal(b, a, bn) ;
    return (errno = EOVERFLOW, 0) ;
  }
  bu_copy_internal(b, a, alen) ;
  bu_zero(b + alen, bn - alen) ;
  return 1 ;
}
