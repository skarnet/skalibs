/* ISC license. */

#include <string.h>
#include <skalibs/stralloc.h>
#include <skalibs/skamisc.h>

int string_quote_nodelim (stralloc *sa, char const *s, size_t len)
{
  return string_quote_nodelim_mustquote(sa, s, len, "\"", 1) ;
}
