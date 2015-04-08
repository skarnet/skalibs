/* ISC license. */

#include <skalibs/config.h>

#ifdef SKALIBS_FLAG_REPLACE_LIBC

#include <skalibs/bytestr.h>

unsigned int str_len (char const *s)
{
  register unsigned int len = 0 ;
  while (*s++) len++ ;
  return len ;
}

#endif
