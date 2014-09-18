/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/skamisc.h>

int string_quote_nodelim (stralloc *sa, char const *s, unsigned int len)
{
  return string_quote_nodelim_mustquote(sa, s, len, "\"", 1) ;
}
