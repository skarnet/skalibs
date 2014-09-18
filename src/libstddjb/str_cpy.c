/* ISC license. */

#include <skalibs/config.h>

#ifdef SKALIBS_FLAG_REPLACE_LIBC

#include <skalibs/bytestr.h>

unsigned int str_copy (char *s, char const *t)
{
  register unsigned int len = 0 ;
  while ((*s = *t)) (s++, t++, len++) ;
  return len ;
}

#endif
