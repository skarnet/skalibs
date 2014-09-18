/* ISC license. */

#include <skalibs/surf.h>
#include <skalibs/unirandom.h>
#include <skalibs/unisurf.h>

int unisurf_sinit (union unirandominfo *u, char const *s)
{
  surf_sinit(&u->surf_ctx, s) ;
  return 1 ;
}

int unisurf_finish (union unirandominfo *u)
{
  (void)u ;
  return 1 ;
}

unsigned int unisurf_read (union unirandominfo *u, char *s, unsigned int n)
{
  surf(&u->surf_ctx, s, n) ;
  return n ;
}
