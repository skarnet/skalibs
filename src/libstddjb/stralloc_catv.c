/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/siovec.h>
#include <skalibs/stralloc.h>

int stralloc_catv (stralloc *sa, siovec_t const *v, unsigned int n)
{
  register unsigned int i = 0 ;
  {
    unsigned int total = 0 ;
    for (; i < n ; i++) total += v[i].len ;
    if (!stralloc_readyplus(sa, total)) return 0 ;
  }
  for (i = 0 ; i < n ; i++)
  {
    byte_copy(sa->s + sa->len, v[i].len, v[i].s) ;
    sa->len += v[i].len ;
  }
  return 1 ;
}
