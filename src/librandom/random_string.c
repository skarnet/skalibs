/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASARC4RANDOM

#include <skalibs/nonposix.h>
#include <stdlib.h>
#include <skalibs/random.h>

void random_string (char *s, size_t n)
{
  arc4random_buf(s, n) ;
}

#else
#ifdef SKALIBS_HASGETRANDOM

#include <sys/random.h>
#include <skalibs/random.h>

void random_string (char *s, size_t n)
{
  while (n)
  {
    ssize_t r = getrandom(s, n, 0) ;
    if (r >= 0)
    {
      s += r ;
      n -= r ;
    }
  }
}

#else
#ifdef SKALIBS_HASDEVURANDOM

#include <skalibs/allreadwrite.h>
#include <skalibs/random.h>
#include "random-internal.h"

void random_string (char *s, size_t n)
{
  size_t r = allread(random_fd, s, n) ;
  if (r < n) surf(&surf_here, s+r, n-r) ;
}

#else /* default */

#include <skalibs/random.h>
#include "random-internal.h"

void random_string (char *s, size_t n)
{
  surf(&surf_here, s, n) ;
}

#endif
#endif
#endif
