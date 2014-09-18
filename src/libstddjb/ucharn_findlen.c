/* ISC license. */

#include <skalibs/fmtscan.h>

unsigned int ucharn_findlen (char const *s)
{
  register unsigned int i = 0 ;
  while (fmtscan_num(s[i], 16) <= 0xF) i++ ;
  return i ;
}
