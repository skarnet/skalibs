/* ISC license. */

#include <unistd.h>
#include <string.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>

int sagethostname (stralloc *sa)
{
  size_t n = 128 ;
  int wasnull = !sa->s ;

  for (;;)
  {
    if (!stralloc_readyplus(sa, n)) goto err ;
    sa->s[sa->len + n - 2] = 0 ;
    if (gethostname(sa->s + sa->len, n) == -1) goto err ;
    if (!sa->s[sa->len + n - 2]) break ;
    n += 128 ;
  }
  sa->len += strlen(sa->s + sa->len) ;
  return 0 ;

err:
  if (wasnull) stralloc_free(sa) ;
  return -1 ;
}
