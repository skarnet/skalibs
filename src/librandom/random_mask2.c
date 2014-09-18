/* ISC license. */

#include <skalibs/sysdeps.h>
#include "random-internal.h"

unsigned int random_mask2 (register unsigned int n)
{
  for (;;)
  {
    register unsigned int m = n | (n >> 1) ;
    if (m == n) return n ;
    n = m ;
  }
}

unsigned int random_nchars (register unsigned int n)
{
  return n <= 0xff ? 1 :
#if SKALIBS_SIZEOFUINT == 2
  2
#else
         n <= 0xffff ? 2 :
         n <= 0xffffffUL ? 3 :
# if SKALIBS_SIZEOFUINT == 4
  4
# else
         n <= 0xffffffffUL ? 4 :
         n <= 0xffffffffffULL ? 5 :
         n <= 0xffffffffffffULL ? 6 :
         n <= 0xffffffffffffffULL ? 7 :
  8
# endif
#endif
 ;
}
