/* ISC license. */

/* MT-unsafe */

#include <skalibs/stralloc.h>
#include <skalibs/skamisc.h>
#include <skalibs/random.h>

int random_sauniquename (stralloc *sa, unsigned int n)
{
  unsigned int base = sa->len ;
  int wasnull = !sa->s ;
  register int r ;
  if (sauniquename(sa) == -1) return -1 ;
  if (!stralloc_readyplus(sa, n+1)) goto err ;
  stralloc_catb(sa, ":", 1) ;
  r = random_name(sa->s + sa->len, n) ;
  if (r == -1) goto err ;
  sa->len += r ;
  return r ;

err:
  if (wasnull) stralloc_free(sa) ; else sa->len = base ;
  return -1 ;
}
