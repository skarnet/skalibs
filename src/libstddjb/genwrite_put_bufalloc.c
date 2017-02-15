/* ISC license. */

#include <sys/types.h>
#include <skalibs/bufalloc.h>
#include <skalibs/genwrite.h>

ssize_t genwrite_put_bufalloc (void *target, char const *s, size_t len)
{
  register bufalloc *ba = target ;
  return bufalloc_put(ba, s, len) ? (ssize_t)len : -1 ;
}
