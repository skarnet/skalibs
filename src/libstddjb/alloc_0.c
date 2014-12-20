/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/alloc.h>
#include "alloc-internal.h"

#ifndef SKALIBS_HASMALLOC0

#define ALIGNMENT 16
static union { unsigned char blah[ALIGNMENT] ; long double ld ; } const zeroblock ;
aligned_char *alloc_0 = (aligned_char_ref)(&zeroblock) ;

#endif
