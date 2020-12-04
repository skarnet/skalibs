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

#include <skalibs/djbunix.h>
#include <skalibs/random.h>

int random_init ()
{
#ifdef SKALIBS_HASDEVURANDOM
  char seed[160] ;
  random_makeseed(seed) ;
  openwritenclose_unsafe("/dev/urandom", seed, 160) ;
#endif
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
  char seed[160] ;
  if (random_fd >= 0) return 1 ;
  random_makeseed(seed) ;
  surf_init(&surf_here, seed) ;
  openwritenclose_unsafe("/dev/urandom", seed, 160) ;
  random_fd = openc_readb("/dev/urandom") ;
  return random_fd >= 0 ;
}

#else /* default */

int random_init ()
{
  char seed[160] ;
  random_makeseed(seed) ;
  surf_init(&surf_here, seed) ;
  return 1 ;
}

#endif
#endif
#endif
