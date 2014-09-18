/* ISC license. */

#include <skalibs/surf.h>
#include "random-internal.h"
#include <skalibs/unirandom.h>
#include <skalibs/unisurf.h>

int unisurf_init (union unirandominfo *u)
{
  surf_init(&u->surf_ctx) ;
  return 1 ;
}

int unirandom_register_surf (unirandom *u)
{
  unirandom_register(u, &unisurf_init, &unisurf_finish, &unisurf_read, &unisurf_read) ;
  return 1 ;
}
