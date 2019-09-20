/* ISC license. */

#ifndef ALLOC_H
#define ALLOC_H

#include <stdlib.h>
#include <skalibs/gccattributes.h>

extern void *alloc (size_t) ;
#define alloc_free(p) free(p)

#define alloc_re(p, old, new) alloc_realloc(p, new)
extern int alloc_realloc (void **, size_t) ;

#endif
