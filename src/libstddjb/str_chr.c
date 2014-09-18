/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/bytestr.h>

#ifndef SKALIBS_FLAG_REPLACE_LIBC

#include <string.h>

unsigned int str_chr (register char const *s, int c)
{
  register char *p = strchr(s, c) ;
  return p ? (unsigned int)(p - s) : strlen(s) ;
}

#else

unsigned int str_chr (register char const *s, int c)
{
  register char ch = c ;
  register char const *t = s ;

  for (;;)
  {
    if (!*t) break; if (*t == ch) break; ++t;
    if (!*t) break; if (*t == ch) break; ++t;
    if (!*t) break; if (*t == ch) break; ++t;
    if (!*t) break; if (*t == ch) break; ++t;
  }
  return t - s ;
}

#endif
