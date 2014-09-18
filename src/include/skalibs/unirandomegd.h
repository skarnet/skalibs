/* ISC license. */

#ifndef UNIRANDOMEGD_H
#define UNIRANDOMEGD_H

#include <skalibs/unirandom.h>

extern int unirandomegd_sinit (union unirandominfo *, char const *) ;
extern unsigned int unirandomegd_readb (union unirandominfo *, char *, unsigned int) ;
extern unsigned int unirandomegd_readnb (union unirandominfo *, char *, unsigned int) ;
extern int unirandomegd_finish (union unirandominfo *) ;

extern int unihasegd_init (union unirandominfo *) ;

#define UNIRANDOM_REGISTER_HASEGD() { .readb = &unirandomegd_readb, .readnb = &unirandomegd_readnb, .init = &unihasegd_init, .finish = &unirandomegd_finish, .data = UNIRANDOMINFO_ZERO, .initted = 0 }

#endif
