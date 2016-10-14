/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASARC4RANDOM

#include <skalibs/nonposix.h>
#include <stdlib.h>
#include <skalibs/random.h>

void random_string (char *s, unsigned int n)
{
  arc4random_buf(s, n) ;
}

#else
#ifdef SKALIBS_HASGETRANDOM

#include <skalibs/nonposix.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <skalibs/random.h>

static int getrandom (void *buf, size_t buflen, unsigned int flags)
{
  return syscall(SYS_getrandom, buf, buflen, flags) ;
}

void random_string (char *s, unsigned int n)
{
  while (n)
  {
    register int r = getrandom(s, n, 0) ;
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

void random_string (char *s, unsigned int n)
{
  unsigned int r = allread(random_fd, s, n) ;
  if (r < n) surf(&surf_here, s+r, n-r) ;
}

#else /* default */

#include <skalibs/random.h>
#include "random-internal.h"

void random_string (char *s, unsigned int n)
{
  surf(&surf_here, s, n) ;
}

#endif
#endif
#endif
