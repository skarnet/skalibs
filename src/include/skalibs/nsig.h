/* ISC license. */

/*
   This header MUST be paired with skalibs/nonposix.h AND
   skalibs/bsdsnowflake.h, both of which must be included
   before system headers.
*/

#ifndef SKALIBS_NSIG_H
#define SKALIBS_NSIG_H

#include <signal.h>

#ifndef NSIG
# ifdef _NSIG
#  define NSIG _NSIG
# elif defined(SIGMAX)
#  define NSIG (SIGMAX + 1)
# elif defined(_SIGMAX)
#  define NSIG(_SIGMAX + 1)
# elif defined(SKALIBS_BSD_SUCKS)
#  define NSIG 64
# else
#  define NSIG 65
# endif
#endif

#ifdef SKALIBS_BSD_SUCKS
# define SKALIBS_NSIG (NSIG+1)
#else
# define SKALIBS_NSIG NSIG
#endif

#endif
