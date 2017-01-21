/* ISC license. */

#include <skalibs/fmtscan.h>
#include <skalibs/biguint.h>

size_t bu_scanlen (char const *s, size_t *zeron)
{
  size_t n = ucharn_findlen(s) ;
  *zeron = n ;
  while (*s == '0') { s++ ; (*zeron)-- ; }
  return n ;
}
