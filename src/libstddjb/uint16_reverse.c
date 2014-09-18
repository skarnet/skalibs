/* ISC license. */

#include <skalibs/uint16.h>

void uint16_reverse (char *s, unsigned int n)
{
  while (n--)
  {
    char c = s[0] ;
    s[0] = s[1] ;
    s[1] = c ;
    s += 2 ;
  }
}
