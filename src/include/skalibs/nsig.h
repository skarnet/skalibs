/* ISC license. */

/*
   This header MUST be paired with skalibs/nonposix.h
   which must be included before system headers.
*/

#ifndef NSIG_H

#include <signal.h>

#define SKALIBS_DEFAULT_NSIG 65

#ifndef NSIG
# define NSIG SKALIBS_DEFAULT_NSIG
#endif


 /* OpenBSD is a fucking snowflake */

#ifdef __OpenBSD__
#define SKALIBS_NSIG (NSIG-1)
#else
#define SKALIBS_NSIG NSIG
#endif

#endif
