/* ISC license. */

#include <skalibs/config.h>
#include <signal.h>
#include <skalibs/sig.h>

int skasigaction (int sig, struct skasigaction const *new, struct skasigaction *old)
{
  struct sigaction sanew, saold ;
  if (((new->flags & SKASA_MASKALL) ? sigfillset(&sanew.sa_mask) : sigemptyset(&sanew.sa_mask)) == -1) return -1 ;
  sanew.sa_handler = new->handler ;
  sanew.sa_flags = (new->flags & SKASA_NOCLDSTOP) ? SA_NOCLDSTOP : 0 ;
#ifndef SKALIBS_FLAG_PREFERSELECT
  sanew.sa_flags |= SA_RESTART ;
#endif
  if (sigaction(sig, &sanew, &saold) < 0) return -1 ;
  if (old)
  {
    int r = sigismember(&saold.sa_mask, (sig == SIGTERM) ? SIGPIPE : SIGTERM) ;
    if (r < 0) return -1 ;
    old->flags = 0 ;
    if (r) old->flags |= SKASA_MASKALL ;
    if (saold.sa_flags & SA_NOCLDSTOP) old->flags |= SKASA_NOCLDSTOP ;
    old->handler = saold.sa_handler ;
  }
  return 0 ;
}
