/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASARC4RANDOM

#include <skalibs/nonposix.h>
#include <stdlib.h>

#include <skalibs/random.h>

int random_init ()
{
#ifdef SKALIBS_HASARC4RANDOM_ADDRANDOM
  char seed[160] ;
  random_makeseed(seed) ;
  arc4random_addrandom((unsigned char *)seed, 160) ;
#endif
  return 1 ;
}

#else
#ifdef SKALIBS_HASGETRANDOM

#include <skalibs/random.h>

int random_init ()
{
  return 1 ;
}

#else

#include <skalibs/surf.h>
#include <skalibs/random.h>
#include "random-internal.h"

SURFSchedule surf_here = SURFSCHEDULE_ZERO ;

#ifdef SKALIBS_HASDEVURANDOM

#include <errno.h>

#include <skalibs/djbunix.h>

int random_fd = -1 ;

int random_init ()
{
  if (random_fd >= 0) return 1 ;
  random_fd = openc_readb("/dev/urandom") ;
  return random_fd >= 0 ;
}

#else /* default */

int random_init ()
{
  static int initted = 0 ;
  if (!initted)
  {
    char seed[160] ;
    initted = 1 ;
    random_makeseed(seed) ;
    surf_init(&surf_here, seed) ;
  }
  return 1 ;
}

#endif
#endif
#endif
