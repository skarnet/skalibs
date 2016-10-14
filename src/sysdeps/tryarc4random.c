/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#include <stdlib.h>

int main (void)
{
  return arc4random_uniform(1) ;
}
