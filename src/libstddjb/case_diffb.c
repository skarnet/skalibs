/* ISC license. */

#include <skalibs/bytestr.h>

int case_diffb (char const *s, unsigned int len, char const *t)
{
  register unsigned char x = 0, y = 0 ;
  unsigned char const d = 'a' - 'A' ;

  while (len-- && (x == y))
  {
    x = *s++ ;
    if (('a' <= x) && (x <= 'z')) x -= d ;
    y = *t++ ;
    if (('a' <= y) && (y <= 'z')) y -= d ;
  }
  return (int)(x - y) ;
}
