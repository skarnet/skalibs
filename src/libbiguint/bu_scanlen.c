/* ISC license. */

#include <skalibs/fmtscan.h>
#include <skalibs/biguint.h>

unsigned int bu_scanlen (char const *s, unsigned int *zeron)
{
  unsigned int n = ucharn_findlen(s) ;
  *zeron = n ;
  while (*s == '0') { s++ ; (*zeron)-- ; }
  return n ;
}
