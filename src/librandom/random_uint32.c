/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASARC4RANDOM

#include <skalibs/nonposix.h>
#include <stdint.h>
#include <stdlib.h>
#include <skalibs/random.h>

uint32_t random_uint32 (uint32_t n)
{
  return arc4random_uniform(n) ;
}

#else

#include <skalibs/uint32.h>
#include <skalibs/random.h>

uint32_t random_uint32 (uint32_t n)
{
  uint32_t min, x ;
  if (n < 2) return 0 ;
  min = -n % n ;
  for (;;)
  {
    char tmp[4] ;
    random_string(tmp, 4) ;
    uint32_unpack_big(tmp, &x) ;
    if (x >= min) break ;
  }
  return x % n ;
}

#endif
