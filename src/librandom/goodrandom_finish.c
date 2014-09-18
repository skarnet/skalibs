/* ISC license. */

/* MT-unsafe */

#include "random-internal.h"
#include <skalibs/rrandom.h>
#include <skalibs/random.h>

void goodrandom_finish (void)
{
  rrandom_finish(&goodrandom_here) ;
}
