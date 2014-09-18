/* ISC license. */

#include <errno.h>
#include <skalibs/bytestr.h>
#include <skalibs/env.h>

int env_make (char const **v, unsigned int argc, char const *s, unsigned int len)
{
  while (argc--)
  {
    register unsigned int n = str_len(s) + 1 ;
    if (n > len) return (errno = EINVAL, 0) ;
    *v++ = s ; s += n ; len -= n ;
  }
  return 1 ;
}
