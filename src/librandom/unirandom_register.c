/* ISC license. */

#include <errno.h>
#include <skalibs/unirandom.h>
#include "random-internal.h"

void unirandom_register (unirandom_ref u, int (*init) (union unirandominfo *), int (*finish) (union unirandominfo *), unsigned int (*readb) (union unirandominfo *, char *, unsigned int), unsigned int (*readnb) (union unirandominfo *, char *, unsigned int))
{
  unirandom zero = UNIRANDOM_ZERO ;
  *u = zero ;
  u->init = init ;
  u->finish = finish ;
  u->readb = readb ;
  u->readnb = readnb ;
  u->initted = 0 ;
}
