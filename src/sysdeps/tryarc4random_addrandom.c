/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#include <stdlib.h>

int main (void)
{
  arc4random_addrandom("", 1) ;
  return 0 ;
}
