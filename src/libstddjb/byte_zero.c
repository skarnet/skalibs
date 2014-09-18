/* ISC license. */

#include <skalibs/config.h>

#ifdef SKALIBS_FLAG_REPLACE_LIBC

#include <skalibs/bytestr.h>

void byte_zero (void *p, register unsigned int n)
{
  register char *s = (char *)p ;
  while (n--) *s++ = 0 ;
}

#endif
