/* ISC license. */

#ifndef RANDOM_INTERNAL_H
#define RANDOM_INTERNAL_H

#include <skalibs/gccattributes.h>
#include <skalibs/surf.h>
#include <skalibs/unirandom.h>
#include <skalibs/rrandom.h>

extern void unirandom_register (unirandom_ref, int (*) (union unirandominfo *), int (*) (union unirandominfo *), unsigned int (*) (union unirandominfo *, char *, unsigned int), unsigned int (*) (union unirandominfo *, char *, unsigned int)) ;

extern unsigned int random_mask2 (unsigned int) gccattr_const ;
extern unsigned int random_nchars (unsigned int) gccattr_const ;

extern SURFSchedule surf_here ;
extern rrandom goodrandom_here ;
extern rrandom badrandom_here ;

#endif
