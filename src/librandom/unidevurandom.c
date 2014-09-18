/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/unirandomdev.h>
#include <skalibs/unirandom.h>

#ifdef SKALIBS_HASDEVURANDOM

#include "random-internal.h"

int unidevurandom_init (union unirandominfo *u)
{
  return unirandomdev_sinit(u, "/dev/urandom") ;
}

int unirandom_register_devurandom (unirandom *u)
{
  unirandom_register(u, &unidevurandom_init, &unirandomdev_finish, &unirandomdev_readb, &unirandomdev_readnb) ;
  return 1 ;
}

#else

#include <errno.h>

int unidevurandom_init (union unirandominfo *u)
{
  (void)u ;
  return (errno = ENOSYS, 0) ;
}

int unirandom_register_devurandom (unirandom *u)
{
  (void)u ;
  return (errno = ENOSYS, 0) ;
}

#endif
