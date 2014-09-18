/* ISC license. */

/* MT-unsafe */

#include <skalibs/sig.h>

int sig_push (int sig, skasighandler_t_ref f)
{
  struct skasigaction ssa = { f, SKASA_MASKALL | SKASA_NOCLDSTOP } ;
  return sig_pusha(sig, &ssa) ;
}
