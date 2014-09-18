/* ISC license. */

#include <signal.h>
#include <skalibs/sig.h>

struct skasigaction const SKASIG_DFL = { SIG_DFL, 0 } ;
struct skasigaction const SKASIG_IGN = { SIG_IGN, 0 } ;
