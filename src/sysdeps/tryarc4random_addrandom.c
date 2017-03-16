/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#include <stdlib.h>

int main (void)
{
  unsigned char *blah = (unsigned char *)"" ;
  arc4random_addrandom(blah, 1) ;
  return 0 ;
}
