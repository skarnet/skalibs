/* ISC license. */

/*
   This header MUST be paired with skalibs/nonposix.h
   which must be included before system headers.
*/

#ifndef NSIG_H

#include <signal.h>

#define SKALIBS_NSIG 65

#ifndef NSIG
# define NSIG SKALIBS_NSIG
#endif

#endif
