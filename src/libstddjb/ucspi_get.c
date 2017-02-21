/* ISC license. */

#include <errno.h>
#include <string.h>
#include <skalibs/env.h>

char const *ucspi_get (char const *s)
{
  char const *x = env_get("PROTO") ;
  if (x)
  {
    size_t len = strlen(s) ;
    size_t xlen = strlen(x) ;
    char tmp[len + xlen + 1] ;
    memcpy(tmp, x, xlen) ;
    memcpy(tmp + xlen, s, len + 1) ;
    x = env_get(tmp) ;
    if (!x) errno = ENOENT ;
  }
  else errno = EINVAL ;
  return x ;
}
