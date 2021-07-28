/* ISC license. */

/* MT-unsafe */

#include <signal.h>

#include <skalibs/functypes.h>
#include <skalibs/sig.h>

int sig_catch (int sig, sig_func_ref f)
{
  struct sigaction action = { .sa_handler = f, .sa_flags = SA_RESTART | SA_NOCLDSTOP } ;
  sigfillset(&action.sa_mask) ;
  return sigaction(sig, &action, 0) >= 0 ;
}
