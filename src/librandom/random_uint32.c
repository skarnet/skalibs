/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASARC4RANDOM

#include <skalibs/nonposix.h>
#include <stdlib.h>
#include <skalibs/random.h>

uint32 random_uint32 (uint32 n)
{
  return arc4random_uniform(n) ;
}

#else

#include <skalibs/uint32.h>
#include <skalibs/bytestr.h>
#include <skalibs/random.h>

static inline uint32 random_mask2 (register uint32 n)
{
  for (;;)
  {
    register uint32 m = n | (n >> 1) ;
    if (m == n) return n ;
    n = m ;
  }
}

static inline unsigned int random_nchars (register uint32 n)
{
  return n <= 0xff ? 1 :
         n <= 0xffff ? 2 :
         n <= 0xffffffUL ? 3 : 4 ;
}

uint32 random_uint32 (uint32 n)
{
  if (!n) return 0 ;
  else
  {
    uint32 i = n, m = random_mask2(n-1) ;
    unsigned int nchars = random_nchars(n) ;
    char tmp[4] ;
    while (i >= n)
    {
      random_string(tmp, nchars) ;
      byte_zero(tmp + nchars, 4 - nchars) ;
      uint32_unpack(tmp, &i) ;
      i &= m ;
    }
    return i ;
  }
}

#endif
