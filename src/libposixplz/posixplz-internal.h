/* ISC license. */

#ifndef POSIXPLZ_INTERNAL_H
#define POSIXPLZ_INTERNAL_H

typedef struct linkarg_s linkarg_t, *linkarg_t_ref ;
struct linkarg_s
{
  linkfunc_t_ref lf ;
  char const *src ;
} ;

extern void execvep_internal (char const *, char const *const *, char const *const *, char const *) ;

#endif
