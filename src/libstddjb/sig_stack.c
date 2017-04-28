/* ISC license. */

#include <skalibs/nonposix.h>
#include <errno.h>
#include <signal.h>
#include <skalibs/sig.h>
#include <skalibs/nsig.h>

static struct skasigaction skasigstack[SKALIBS_NSIG-1][SIGSTACKSIZE] ;
static unsigned int sigsp[SKALIBS_NSIG-1] ;

int sig_pusha (int sig, struct skasigaction const *ssa)
{
  if ((sig <= 0) || (sig >= SKALIBS_NSIG)) return (errno = EINVAL, -1) ;
  if (sigsp[sig-1] >= SIGSTACKSIZE) return (errno = ENOBUFS, -1) ;
  if (skasigaction(sig, ssa, &skasigstack[sig-1][sigsp[sig-1]]) == -1)
      return -1 ;
  return ++sigsp[sig-1] ;
}

int sig_pop (int sig)
{
  if ((sig <= 0) || (sig >= SKALIBS_NSIG)) return (errno = EINVAL, -1) ;
  if (!sigsp[sig-1]) return (errno = EFAULT, -1);
  if (skasigaction(sig, &skasigstack[sig-1][sigsp[sig-1]-1], 0) == -1)
    return -1 ;
  return --sigsp[sig-1] ;
}
