/* ISC license. */

#include <skalibs/config.h>

#ifdef SKALIBS_FLAG_REPLACE_LIBC

#include <skalibs/bytestr.h>

void byte_copy (register char *to, register unsigned int n, register char const *from)
{
  while (n--) *to++ = *from++ ;
}

#endif
