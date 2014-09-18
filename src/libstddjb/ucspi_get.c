/* ISC license. */

#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/env.h>

char const *ucspi_get (char const *s)
{
  char const *x = env_get("PROTO") ;
  if (x)
  {
    unsigned int len = str_len(s) ;
    unsigned int xlen = str_len(x) ;
    char tmp[len + xlen + 1] ;
    byte_copy(tmp, xlen, x) ;
    byte_copy(tmp + xlen, len + 1, s) ;
    x = env_get(tmp) ;
    if (!x) errno = ENOENT ;
  }
  else errno = EINVAL ;
  return x ;
}
