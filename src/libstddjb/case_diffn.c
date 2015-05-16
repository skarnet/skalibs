/* ISC license. */

#include <skalibs/config.h>
#include <skalibs/bytestr.h>

#ifdef SKALIBS_FLAG_REPLACE_LIBC

int case_diffn (char const *s, char const *t, unsigned int len)
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

#endif
