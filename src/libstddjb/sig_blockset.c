/* ISC license. */

#include <signal.h>
#include <skalibs/sig.h>

void sig_blockset (sigset_t const *set)
{
  sigprocmask(SIG_SETMASK, set, 0) ;
}
