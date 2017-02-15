/* ISC license. */

#include <sys/types.h>
#include <skalibs/bufalloc.h>

size_t bufalloc_getlen (bufalloc const *ba)
{
  return bufalloc_len(ba) ;
}
