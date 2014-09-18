/* ISC license. */

/* MT-unsafe */

#include "random-internal.h"
#include <skalibs/random.h>

unsigned char badrandom_char (void)
{
  unsigned char x ;
  badrandom_string((char *)&x, 1) ;
  return x ;
}
