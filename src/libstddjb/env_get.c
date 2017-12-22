/* ISC license. */

#include <stdlib.h>
#include <skalibs/posixplz.h>

char const *env_get (char const *s)
{
  return getenv(s) ;
}
