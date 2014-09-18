/* ISC license. */

#include <skalibs/bufalloc.h>
#include <skalibs/genwrite.h>

int genwrite_flush_bufalloc (void *target)
{
  register bufalloc *ba = target ;
  return bufalloc_flush(ba) ;
}
