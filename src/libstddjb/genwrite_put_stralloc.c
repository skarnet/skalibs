/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/genwrite.h>

int genwrite_put_stralloc (void *target, char const *s, unsigned int len)
{
  register stralloc *sa = target ;
  return stralloc_catb(sa, s, len) ? (int)len : -1 ;
}
