/* ISC license. */

#include <skalibs/bytestr.h>

unsigned int byte_rchr (register char const *s, unsigned int n, int c)
{
  register unsigned int i = n ;
  register char ch = c ;
  s += n ;
  while (i--) if (*--s == ch) return i ;
  return n ;
}
