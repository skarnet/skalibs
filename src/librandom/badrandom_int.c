/* ISC license. */

/* MT-unsafe */

#include <skalibs/rrandom.h>
#include "random-internal.h"
#include <skalibs/random.h>

unsigned int badrandom_int (unsigned int n)
{
  return rrandom_readint(&badrandom_here, n, &unirandom_readnb) ;
}
