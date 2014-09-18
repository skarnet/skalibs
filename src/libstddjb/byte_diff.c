/* ISC license. */

#include <skalibs/config.h>

#ifdef SKALIBS_FLAG_REPLACE_LIBC

#include <skalibs/bytestr.h>

int byte_diff (register char const *s, register unsigned int n, register char const *t)
{
  for (;;)
  {
    if (!n) return 0; if (*s != *t) break; ++s; ++t; --n;
    if (!n) return 0; if (*s != *t) break; ++s; ++t; --n;
    if (!n) return 0; if (*s != *t) break; ++s; ++t; --n;
    if (!n) return 0; if (*s != *t) break; ++s; ++t; --n;
  }
  return ((int)(unsigned int)(unsigned char) *s)
       - ((int)(unsigned int)(unsigned char) *t) ;
}

#endif
