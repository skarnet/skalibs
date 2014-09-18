/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/stralloc.h>

int stralloc_catb (stralloc *sa, char const *s, unsigned int n)
{
  if (!stralloc_readyplus(sa, n)) return 0 ;
  byte_copy(sa->s + sa->len, n, s) ;
  sa->len += n ;
  return 1 ;
}
