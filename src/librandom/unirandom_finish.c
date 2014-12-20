/* ISC license. */

#include <errno.h>
#include <skalibs/unirandom.h>

int unirandom_finish (unirandom *u)
{
  if (!u->initted) return 1 ;
  if (!(*u->finish)(&u->data)) return 0 ;
  u->initted = 0 ;
  return 1 ;
}
