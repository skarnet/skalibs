/* ISC license. */

/* MT-unsafe */

#include <sys/types.h>
#include <skalibs/stralloc.h>
#include <skalibs/skamisc.h>
#include <skalibs/random.h>

int random_sauniquename (stralloc *sa, size_t n)
{
  size_t base = sa->len ;
  int wasnull = !sa->s ;
  if (!sauniquename(sa)) return 0 ;
  if (!stralloc_readyplus(sa, n+1)) goto err ;
  stralloc_catb(sa, ":", 1) ;
  random_name(sa->s + sa->len, n) ;
  sa->len += n ;
  return 1 ;

err:
  if (wasnull) stralloc_free(sa) ; else sa->len = base ;
  return 0 ;
}
