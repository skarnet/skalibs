/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/unirandomdev.h>
#include <skalibs/unirandom.h>

#ifdef SKALIBS_HASDEVRANDOM

#include "random-internal.h"

int unidevrandom_init (union unirandominfo *u)
{
  return unirandomdev_sinit(u, "/dev/random") ;
}

int unirandom_register_devrandom (unirandom *u)
{
  unirandom_register(u, &unidevrandom_init, &unirandomdev_finish, &unirandomdev_readb, &unirandomdev_readnb) ;
  return 1 ;
}

#else

#include <errno.h>

int unidevrandom_init (union unirandominfo *u)
{
  (void)u ;
  return (errno = ENOSYS, 0) ;
}

int unirandom_register_devrandom (unirandom *u)
{
  (void)u ;
  return (errno = ENOSYS, 0) ;
}

#endif
