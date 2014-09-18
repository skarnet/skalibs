/* ISC license. */

#include <skalibs/iobuffer.h>

int iobuffer_salvage (iobuffer_ref b)
{
  iobufferu u ;
  if (!b->isk) return 1 ;
  if (!iobufferu_init(&u, b->x.k.fd[0], b->x.k.fd[1])) return 0 ;
  if (!iobuffer_ufromk(&u, &b->x.k)) goto err ;
  iobufferk_finish(&b->x.k) ;
  b->x.u = u ;
  b->isk = 0 ;
  return 1 ;

err:
  iobufferu_finish(&u) ;
  return 0 ;
}
