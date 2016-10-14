/* ISC license. */

#include <skalibs/random.h>

unsigned char random_char (void)
{
  unsigned char c ;
  random_string((char *)&c, 1) ;
  return c ;
}
