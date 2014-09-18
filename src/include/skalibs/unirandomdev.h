/* ISC license. */

#ifndef UNIRANDOMDEV_H
#define UNIRANDOMDEV_H

#include <skalibs/unirandom.h>

extern int unirandomdev_sinit (union unirandominfo *, char const *) ;
extern unsigned int unirandomdev_readb (union unirandominfo *, char *, unsigned int) ;
extern unsigned int unirandomdev_readnb (union unirandominfo *, char *, unsigned int) ;
extern int unirandomdev_finish (union unirandominfo *) ;

extern int unidevrandom_init (union unirandominfo *) ;
extern int unidevurandom_init (union unirandominfo *) ;

#define UNIRANDOM_REGISTER_DEVRANDOM() { .readb = &unirandomdev_readb, .readnb = &unirandomdev_readnb, .init = &unidevrandom_init, .finish = &unirandomdev_finish, .data = UNIRANDOMINFO_ZERO, .initted = 0 }
#define UNIRANDOM_REGISTER_DEVURANDOM() { .readb = &unirandomdev_readb, .readnb = &unirandomdev_readnb, .init = &unidevurandom_init, .finish = &unirandomdev_finish, .data = UNIRANDOMINFO_ZERO, .initted = 0 }

#endif
