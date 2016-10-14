/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASARC4RANDOM

#include <skalibs/nonposix.h>
#include <stdlib.h>
#include <skalibs/random.h>

int random_init ()
{
  char seed[160] ;
  random_makeseed(seed) ;
  arc4random_addrandom(seed, 160) ;
  return 1 ;
}

#else
#ifdef SKALIBS_HASGETRANDOM

#include <skalibs/djbunix.h>
#include <skalibs/random.h>

int random_init ()
{
  char seed[160] ;
  random_makeseed(seed) ;
  return openwritenclose_unsafe("/dev/urandom", seed, 160) ;
}

#else
#ifdef SKALIBS_HASDEVURANDOM

#include <skalibs/djbunix.h>
#include <skalibs/random.h>
#include "random-internal.h"

int random_fd = -1 ;
SURFSchedule surf_here = SURFSCHEDULE_ZERO ;

int random_init ()
{
  int fd ;
  char seed[160] ;
  random_makeseed(seed) ;
  surf_init(&surf_here, seed) ;
  if (!openwritenclose_unsafe("/dev/urandom", seed, 160)) return 0 ;
  if (random_fd < 0)
  {
    fd = open_readb("/dev/urandom") ;
    if (fd < 0) return 0 ;
    if (coe(fd) < 0) { fd_close(fd) ; return 0 ; }
    random_fd = fd ;
  }
  return 1 ;
}

#else /* default */

#include <skalibs/random.h>
#include "random-internal.h"

SURFSchedule surf_here = SURFSCHEDULE_ZERO ;

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
