/* ISC license. */

#include <skalibs/bytestr.h>

unsigned int byte_count (register char const *s, register unsigned int len, register char b)
{
  register unsigned int n = 0 ;
  while (len--) if (*s++ == b) n++ ;
  return n ;
}
