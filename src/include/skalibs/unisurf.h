/* ISC license. */

#ifndef UNISURF_H
#define UNISURF_H

#include <skalibs/unirandom.h>

extern int unisurf_sinit (union unirandominfo *, char const *) ;
extern unsigned int unisurf_read (union unirandominfo *, char *, unsigned int) ;
extern int unisurf_finish (union unirandominfo *) ;

extern int unisurf_init (union unirandominfo *) ;

#define UNIRANDOM_REGISTER_SURF() { .readb = &unisurf_read, .readnb = &unisurf_read, .init = &unisurf_init, .finish = &unisurf_finish, .data = UNIRANDOMINFO_ZERO, .initted = 0 }

#endif
