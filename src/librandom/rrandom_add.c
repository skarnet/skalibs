/* ISC license. */

#include <errno.h>
#include <skalibs/unirandom.h>
#include <skalibs/rrandom.h>

int rrandom_add (rrandom *z, int (*f) (unirandom *))
{
  if (z->n >= 3) return (errno = EBUSY, 0) ;
  if (!(*f)(&z->tries[z->n].it)) return 0 ;
  z->tries[z->n++].ok = 3 ;
  return 1 ;
}
