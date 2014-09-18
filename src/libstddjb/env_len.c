/* ISC license. */

#include <skalibs/env.h>

unsigned int env_len (register char const *const *e)
{
  register unsigned int i = 0 ;
  while (*e++) i++ ;
  return i ;
}
