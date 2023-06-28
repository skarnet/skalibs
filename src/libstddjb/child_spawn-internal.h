/* ISC license. */

#ifndef CHILD_SPAWN_INTERNAL_H
#define CHILD_SPAWN_INTERNAL_H

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASPOSIXSPAWNEARLYRETURN

#include <sys/types.h>

extern pid_t child_spawn_workaround (pid_t, int const *) ;  /* closes the pipe */

#endif

#endif
