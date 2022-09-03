/* ISC license. */

/* MT-unsafe */

#include <skalibs/nonposix.h>
#include <skalibs/bsdsnowflake.h>

#include <signal.h>
#include <errno.h>

#include <skalibs/functypes.h>
#include <skalibs/sig.h>
#include <skalibs/nsig.h>

 /*
   BSD fails sigaction() with EINVAL on non-catchable signals, whereas
   every reasonable OS succeeds and simply ignores the signal handler.
 */

int sig_catch (int sig, sig_func_ref f)
{
  struct sigaction action = { .sa_handler = f, .sa_flags = SA_RESTART | SA_NOCLDSTOP } ;
  sigfillset(&action.sa_mask) ;
  return sigaction(sig, &action, 0) >= 0
#ifdef SKALIBS_BSD_SUCKS
 || (errno == EINVAL && sig >= 1 && sig <= NSIG)
#endif
 ;
}
