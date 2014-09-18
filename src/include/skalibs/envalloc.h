/* ISC license. */

#ifndef ENVALLOC_H
#define ENVALLOC_H

#include <skalibs/genalloc.h>

#define ENVALLOC_ZERO GENALLOC_ZERO

extern int envalloc_make (genalloc *, unsigned int, char const *, unsigned int) ;
extern int envalloc_uniq (genalloc *, char) ;
extern int envalloc_merge (genalloc *, char const *const *, unsigned int, char const *, unsigned int) ;
extern int envalloc_0 (genalloc *) ;

#endif
