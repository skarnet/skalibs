/* ISC license. */

#ifndef SKALIBS_SIG_INTERNAL_H
#define SKALIBS_SIG_INTERNAL_H

typedef struct sigtable_s sigtable, *sigtable_ref ;
struct sigtable_s
{
  int number ;
  char const *name ;
} ;

extern sigtable const skalibs_sigtable[] ;

#endif
