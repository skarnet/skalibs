/* ISC license. */

#include <errno.h>
#include <skalibs/unirandom.h>

unsigned int unirandom_readnb (unirandom *u, char *s, unsigned int n)
{
  if (!u->initted && !unirandom_init(u)) return 0 ;
  return (*u->readnb)(&u->data, s, n) ;
}
