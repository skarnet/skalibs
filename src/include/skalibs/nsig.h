/* ISC license. */

#ifndef NSIG_H

#include <skalibs/nonposix.h>
#include <signal.h>

#define SKALIBS_NSIG 64

#ifndef NSIG
# define NSIG SKALIBS_NSIG
#endif

#endif
