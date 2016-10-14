/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASARC4RANDOM

#include <skalibs/random.h>

void random_finish ()
{
}

#else
#ifdef SKALIBS_HASGETRANDOM

#include <skalibs/random.h>

void random_finish ()
{
}

#else
#ifdef SKALIBS_HASDEVURANDOM

#include <skalibs/djbunix.h>
#include <skalibs/random.h>
#include "random-internal.h"

void random_finish ()
{
  fd_close(random_fd) ;
  random_fd = -1 ;
}

#else /* default */

#include <skalibs/random.h>

void random_finish ()
{
}

#endif
#endif
#endif
