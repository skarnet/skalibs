/* ISC license. */

#include <unistd.h>
#include <skalibs/djbunix.h>
#include <skalibs/skamisc.h>
#include <skalibs/stralloc.h>
#include <skalibs/tai.h>
#include <skalibs/uint.h>

int sauniquename (stralloc *sa)
{
  unsigned int base = sa->len ;
  int wasnull = !sa->s ;

  if (!stralloc_readyplus(sa, TIMESTAMP + UINT_FMT + 131)) return 0 ;
  sa->s[base] = ':' ;
  timestamp(sa->s + base + 1) ;
  sa->s[base + 1 + TIMESTAMP] = ':' ;
  sa->len = base + 2 + TIMESTAMP ;
  sa->len += uint_fmt(sa->s + sa->len, getpid()) ;
  sa->s[sa->len++] = ':' ;
  if (sagethostname(sa) == -1) goto err ;
  return 1 ;

err:
  if (wasnull) stralloc_free(sa) ; else sa->len = base ;
  return 0 ;
}
