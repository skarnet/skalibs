/* ISC license. */

#include <errno.h>
#include <skalibs/skamisc.h>

int string_unquote_nodelim (char *d, char const *s, unsigned int len)
{
  unsigned int rr, ww ;
  if (!string_unquote_withdelim(d, &ww, s, len, &rr, 0, 0)) return -1 ;
  return (int)ww ;
}
