/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/bytestr.h>

#ifdef SKALIBS_FLAG_REPLACE_LIBC

int str_diffn (register char const *s, register char const *t, register unsigned int len)
{
  while (len--)
  {
    if (*s != *t) return *s - *t ;
    if (!*s) break ;
    s++ ; t++ ;
  }
  return 0 ;
}

#endif
