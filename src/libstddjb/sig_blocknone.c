/* ISC license. */

#include <signal.h>
#include <skalibs/sig.h>

void sig_blocknone (void)
{
  sigset_t ss ;
  sigemptyset(&ss) ;
  sigprocmask(SIG_SETMASK, &ss, 0) ;
}
