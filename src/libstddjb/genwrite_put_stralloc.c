/* ISC license. */

#include <sys/types.h>
#include <skalibs/stralloc.h>
#include <skalibs/genwrite.h>

ssize_t genwrite_put_stralloc (void *target, char const *s, size_t len)
{
  register stralloc *sa = target ;
  return stralloc_catb(sa, s, len) ? (ssize_t)len : -1 ;
}
