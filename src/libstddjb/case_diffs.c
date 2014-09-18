/* ISC license. */

#include <skalibs/bytestr.h>

int case_diffs (char const *s, char const *t)
{
  register unsigned char x = 1, y = 1 ;
  unsigned char const d = 'a' - 'A' ;

  while (x && (x == y))
  {
    x = *s++ ;
    if (('a' <= x) && (x <= 'z')) x -= d ;
    y = *t++ ;
    if (('a' <= y) && (y <= 'z')) y -= d ;
  }
  return (int)(x - y) ;
}
