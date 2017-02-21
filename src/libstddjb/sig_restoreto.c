/* ISC license. */

/* MT-unsafe */

#include <signal.h>
#include <skalibs/sig.h>

void sig_restoreto (sigset_t const *set, unsigned int n)
{
  unsigned int i = 1 ;
  for (; i <= n ; i++)
  {
    int h = sigismember(set, i) ;
    if (h < 0) continue ;
    if (h) sig_restore(i) ;
  }
}
