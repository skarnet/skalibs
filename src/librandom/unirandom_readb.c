/* ISC license. */

#include <errno.h>
#include <skalibs/unirandom.h>

unsigned int unirandom_readb (unirandom *u, char *s, unsigned int n)
{
  if (!u->initted && !unirandom_init(u)) return 0 ;
  return (*u->readb)(&u->data, s, n) ;
}
