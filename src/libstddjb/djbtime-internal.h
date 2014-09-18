/* ISC license. */

#ifndef DJBTIME_INTERNAL_H
#define DJBTIME_INTERNAL_H

#include <skalibs/uint64.h>


/* Leap second handling, for UTC <--> TAI conversions */

#define LEAPSECS_MAX 39
#define LEAPSECS_FILE SKALIBS_ETC "/leapsecs.dat"
extern uint64 *leapsecs_here ;

extern int leapsecs_init_r (char const *, uint64 *) ;
#define leapsecs_init() leapsecs_init_r(LEAPSECS_FILE, leapsecs_here)
extern int leapsecs_add_r (uint64 *, char const *, uint64 *, int) ;
#define leapsecs_add(t, h) leapsecs_add_r(t, LEAPSECS_FILE, leapsecs_here, h)
extern int leapsecs_sub_r (uint64 *, char const *, uint64 *) ;
#define leapsecs_sub(t) leapsecs_sub_r((t), LEAPSECS_FILE, leapsecs_here)


#endif
