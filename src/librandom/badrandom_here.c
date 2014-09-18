/* ISC license. */

/* MT-unsafe */

#include <skalibs/sysdeps.h>
#include <skalibs/config.h>
#include <skalibs/unisurf.h>
#include "random-internal.h"

#ifdef SKALIBS_EGD

# include <skalibs/unirandomegd.h>

# ifdef SKALIBS_HASDEVURANDOM

# include <skalibs/unirandomdev.h>

rrandom badrandom_here = { { { UNIRANDOM_REGISTER_DEVURANDOM(), 3 }, { UNIRANDOM_REGISTER_HASEGD(), 3 }, { UNIRANDOM_REGISTER_SURF(), 3 } }, 3 } ;

# else

rrandom badrandom_here = { { { UNIRANDOM_REGISTER_HASEGD(), 3 }, { UNIRANDOM_REGISTER_SURF(), 3 }, { UNIRANDOM_ZERO, 3 } }, 2 } ;

# endif

#else

# ifdef SKALIBS_HASDEVURANDOM

# include <skalibs/unirandomdev.h>

rrandom badrandom_here = { { { UNIRANDOM_REGISTER_DEVURANDOM(), 3 }, { UNIRANDOM_REGISTER_SURF(), 3 }, { UNIRANDOM_ZERO, 3 } }, 2 } ;

# else

rrandom badrandom_here = { { { UNIRANDOM_REGISTER_SURF(), 3 }, { UNIRANDOM_ZERO, 3 }, { UNIRANDOM_ZERO, 3 } }, 1 } ;

# endif

#endif
