/* ISC license. */

#include <signal.h>
#include <skalibs/sig.h>

void sig_pause (void)
{
  sigset_t ss ;
  sigemptyset(&ss) ;
  sigsuspend(&ss) ;
}
