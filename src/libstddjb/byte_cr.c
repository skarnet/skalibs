/* ISC license. */

#include <skalibs/config.h>

#ifdef SKALIBS_FLAG_REPLACE_LIBC

#include <skalibs/bytestr.h>

void byte_copyr (register char *to, register unsigned int n, register char const *from)
{
  to += n ;
  from += n ;
  for (;;)
  {
    if (!n) return; *--to = *--from; --n;
    if (!n) return; *--to = *--from; --n;
    if (!n) return; *--to = *--from; --n;
    if (!n) return; *--to = *--from; --n;
  }
}

#endif
