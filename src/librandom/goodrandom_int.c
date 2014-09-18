/* ISC license. */

/* MT-unsafe */

#include <skalibs/rrandom.h>
#include "random-internal.h"
#include <skalibs/random.h>

unsigned int goodrandom_int (unsigned int n)
{
  return rrandom_readint(&goodrandom_here, n, &unirandom_readb) ;
}
