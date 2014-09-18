/* ISC license. */

#include <errno.h>
#include <skalibs/alloc.h>
#include <skalibs/stralloc.h>

int stralloc_ready_tuned (stralloc *sa, unsigned int n, unsigned int base, unsigned int a, unsigned int b)
{
  register unsigned int t ;
  if (!b) return (errno = EINVAL, 0) ;
  t = n + base + a * n / b ;
  if (t < n) return (errno = ERANGE, 0) ;
  if (!sa->s)
  {
    sa->s = alloc(t) ;
    if (!sa->s) return 0 ;
    sa->a = t ;
  }
  else if (n > sa->a)
  {
    if (!alloc_re(&sa->s, sa->a, t)) return 0 ;
    sa->a = t ;
  }
  return 1 ;
}
