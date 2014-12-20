/* ISC license. */

#include <skalibs/iobuffer.h>

int iobuffer_init (iobuffer *b, int fdin, int fdout)
{
  if (!iobufferk_init(&b->x.k, fdin, fdout)) goto user ;
  if (!iobufferk_isworking(&b->x.k)) goto fk ;
  b->isk = 1 ;
  return 1 ;
 fk:
  iobufferk_finish(&b->x.k) ;
 user:
  if (!iobufferu_init(&b->x.u, fdin, fdout)) return 0 ;
  b->isk = 0 ;
  return 1 ;
}
