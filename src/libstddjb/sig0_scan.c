/* ISC license. */

#include <sys/types.h>
#include <skalibs/sig.h>

size_t sig0_scan (char const *s, int *sig)
{
  int t ;
  size_t len = sig_scan(s, &t) ;
  if (!len || s[len]) return 0 ;
  *sig = t ;
  return len ;
}
