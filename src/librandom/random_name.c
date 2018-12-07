/* ISC license. */

#include <skalibs/random.h>
#include "random-internal.h"

void random_name (char *s, size_t n)
{
  random_string(s, n) ;
  while (n--) s[n] = random_oklist[s[n] & 63] ;
}
