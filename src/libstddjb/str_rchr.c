/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/bytestr.h>

#ifndef SKALIBS_FLAG_REPLACE_LIBC

#include <string.h>

unsigned int str_rchr (register char const *s, int c)
{
  register char *p = strrchr(s, c) ;
  return p ? (unsigned int)(p - s) : (unsigned int)strlen(s) ;
}

#else

unsigned int str_rchr (register char const *s, int c)
{
  register char ch = c ;
  register char const *t = s ;
  register char const *u = 0 ;
  for ( ; *t ; t++) if (*t == ch) u = t ;
  if (!u) u = t ;
  return u - s ;
}

#endif
