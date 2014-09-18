/* ISC license. */

#include <skalibs/bufalloc.h>

unsigned int bufalloc_getlen (bufalloc const *ba)
{
  return bufalloc_len(ba) ;
}
