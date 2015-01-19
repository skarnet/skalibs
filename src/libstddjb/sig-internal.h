/* ISC license. */

#ifndef SIG_INTERNAL
#define SIG_INTERNAL

typedef struct sigtable_s sigtable_t, *sigtable_t_ref ;
struct sigtable_s
{
  int number ;
  char const *name ;
} ;

extern sigtable_t const skalibs_sigtable[] ;

#endif
