/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#include <string.h>

int main (void)
{
  return strnlen("/", 1) ;
}
