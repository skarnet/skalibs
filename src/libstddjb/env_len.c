/* ISC license. */

#include <sys/types.h>
#include <skalibs/env.h>

size_t env_len (char const *const *e)
{
  size_t i = 0 ;
  while (*e++) i++ ;
  return i ;
}
