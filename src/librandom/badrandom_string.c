/* ISC license. */

/* MT-unsafe */

#include <skalibs/rrandom.h>
#include "random-internal.h"
#include <skalibs/random.h>

unsigned int badrandom_string (char *s, unsigned int n)
{
  return rrandom_readnb(&badrandom_here, s, n) ;
}
