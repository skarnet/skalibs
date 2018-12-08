/* ISC license. */

#include <skalibs/surf.h>
#include "random-internal.h"

void autosurf_name (char *s, size_t n)
{
  autosurf(s, n) ;
  while (n--) s[n] = random_oklist[s[n] & 63] ;
}
