/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/env.h>

int env_addmodif (stralloc *sa, char const *s, char const *t)
{
  unsigned int oldlen = sa->len ;
  if (!s) return 1 ;
  if (!stralloc_cats(sa, s)) return 0 ;
  if ((t && (!stralloc_catb(sa, "=", 1) || !stralloc_cats(sa, t)))
   || !stralloc_0(sa))
  {
    sa->len = oldlen ;
    return 0 ;
  }
  return 1 ;
}
