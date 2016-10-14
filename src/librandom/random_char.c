/* ISC license. */

#include <skalibs/random.h>

unsigned char badrandom_char (void)
{
  unsigned char c ;
  random_string((char *)&c, 1) ;
  return c ;
}
