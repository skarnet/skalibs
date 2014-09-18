/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/skamisc.h>

int string_quote (stralloc *sa, char const *s, unsigned int len)
{
  unsigned int base = sa->len ;
  int wasnull = !sa->s ;
  if (!stralloc_catb(sa, "\"", 1)) return 0 ;
  if (!string_quote_nodelim(sa, s, len) || !stralloc_catb(sa, "\"", 1))
  {
    if (wasnull) stralloc_free(sa) ; else sa->len = base ;
    return 0 ;
  }
  return 1 ;
}
