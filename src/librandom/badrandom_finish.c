/* ISC license. */

/* MT-unsafe */

#include <skalibs/rrandom.h>
#include "random-internal.h"
#include <skalibs/random.h>

void badrandom_finish (void)
{
  rrandom_finish(&badrandom_here) ;
}
