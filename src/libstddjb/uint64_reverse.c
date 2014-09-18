/* ISC license. */

#include <skalibs/uint64.h>

void uint64_reverse (char *s, unsigned int n)
{
  while (n--)
  {
    char c = s[0] ; s[0] = s[7] ; s[7] = c ;
    c = s[1] ; s[1] = s[6] ; s[6] = c ;
    c = s[2] ; s[2] = s[5] ; s[5] = c ;
    c = s[3] ; s[3] = s[4] ; s[4] = c ;
    s += 8 ;
  }
}
