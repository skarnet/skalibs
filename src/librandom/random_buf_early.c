/* ISC license. */

#include <skalibs/sysdeps.h>

#if defined(SKALIBS_HASARC4RANDOM)

#include <skalibs/nonposix.h>
#include <stdlib.h>
#include <skalibs/random.h>

void random_buf_early (char *s, size_t n)
{
  arc4random_buf(s, n) ;
}

#elif defined(SKALIBS_HASGETRANDOM) && defined(SKALIBS_HASGRNDINSECURE)

#include <sys/random.h>

#include <skalibs/random.h>

void random_buf_early (char *s, size_t n)
{
  while (n)
  {
    ssize_t r = getrandom(s, n, GRND_INSECURE) ;
    if (r >= 0)
    {
      s += r ;
      n -= r ;
    }
  }
}

#elif defined(SKALIBS_HASDEVURANDOM)

#include "random-internal.h"

void random_buf_early (char *s, size_t n)
{
  random_devurandom(s, n) ;
}

#else

#include <skalibs/surf.h>
#include <skalibs/random.h>

void random_buf_early (char *s, size_t n)
{
  autosurf(s, n) ;
}

#endif
