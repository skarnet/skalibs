/* ISC license. */

#include <signal.h>
#include <skalibs/sig.h>

void sig_unshield (void)
{
  sigset_t ss ;
  sigemptyset(&ss) ;
  sigaddset(&ss, SIGTERM) ;
  sigaddset(&ss, SIGQUIT) ;
  sigaddset(&ss, SIGABRT) ;
  sigaddset(&ss, SIGINT) ;
  sigaddset(&ss, SIGPIPE) ;
  sigaddset(&ss, SIGHUP) ;
  sigprocmask(SIG_UNBLOCK, &ss, 0) ;
}
