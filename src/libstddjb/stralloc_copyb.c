/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/stralloc.h>

int stralloc_copyb (stralloc *sa, char const *s, unsigned int n)
{
  if (!stralloc_ready(sa, n)) return 0 ;
  byte_copy(sa->s, n, s) ;
  sa->len = n ;
  return 1 ;
}
