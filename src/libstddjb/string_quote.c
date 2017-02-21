/* ISC license. */

#include <string.h>
#include <skalibs/stralloc.h>
#include <skalibs/skamisc.h>

int string_quote (stralloc *sa, char const *s, size_t len)
{
  size_t base = sa->len ;
  int wasnull = !sa->s ;
  if (!stralloc_catb(sa, "\"", 1)) return 0 ;
  if (!string_quote_nodelim(sa, s, len) || !stralloc_catb(sa, "\"", 1))
  {
    if (wasnull) stralloc_free(sa) ; else sa->len = base ;
    return 0 ;
  }
  return 1 ;
}
