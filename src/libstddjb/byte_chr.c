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
  register unsigned int i = 0 ;
  register char ch = c ;
  for (; i < n && *s++ != ch ; i++) ;
  return i ;
}

#endif
