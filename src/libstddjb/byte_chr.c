/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/bytestr.h>

#ifndef SKALIBS_FLAG_REPLACE_LIBC

#include <string.h>

unsigned int byte_chr (char const *s, unsigned int n, int c)
{
  register void *p = memchr(s, c, n) ;
  return p ? (unsigned int)((char *)p - s) : n ;
}

#else

unsigned int byte_chr (char const *s, unsigned int n, int c)
{
  register char ch = c ;
  register char const *t = s ;

  for (;;)
  {
    if (!n) break; if (*t == ch) break; ++t; --n;
    if (!n) break; if (*t == ch) break; ++t; --n;
    if (!n) break; if (*t == ch) break; ++t; --n;
    if (!n) break; if (*t == ch) break; ++t; --n;
  }
  return t - s ;
}

#endif
