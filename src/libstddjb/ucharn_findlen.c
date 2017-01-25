/* ISC license. */

#include <sys/types.h>
#include <skalibs/fmtscan.h>

size_t ucharn_findlen (char const *s)
{
  register size_t i = 0 ;
  while (fmtscan_num(s[i], 16) <= 0xF) i++ ;
  return i ;
}
