/* ISC license. */

#include <skalibs/uint.h>
#include <skalibs/unirandom.h>
#include "random-internal.h"
#include <skalibs/rrandom.h>

unsigned int rrandom_readint (rrandom_ref z, unsigned int n, unsigned int (*f) (unirandom_ref, char *, unsigned int))
{
  if (!n) return 0 ;
  else
  {
    unsigned int i = n, nchars = random_nchars(n), m = random_mask2(n-1) ;
    char tmp[UINT_PACK] ;
    while (i >= n)
    {
      if (rrandom_read(z, tmp, nchars, f) < nchars) return 0 ;
      byte_zero(tmp + nchars, UINT_PACK - nchars) ;
      uint_unpack(tmp, &i) ;
      i &= m ;
    }
    return i ;
  }
}
