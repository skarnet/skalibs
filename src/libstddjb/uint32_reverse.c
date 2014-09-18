/* ISC license. */

#include <skalibs/uint32.h>

void uint32_reverse (char *s, unsigned int n)
{
  while (n--)
  {
    char c = s[0] ;
    s[0] = s[3] ;
    s[3] = c ;
    c = s[1] ;
    s[1] = s[2] ;
    s[2] = c ;
    s += 4 ;
  }
}
