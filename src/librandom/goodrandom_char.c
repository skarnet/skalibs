/* ISC license. */

/* MT-unsafe */

#include "random-internal.h"
#include <skalibs/random.h>

unsigned char goodrandom_char (void)
{
  unsigned char x ;
  goodrandom_string((char *)&x, 1) ;
  return x ;
}
