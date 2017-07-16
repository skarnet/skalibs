/* ISC license. */

#ifndef SKALIBS_SETGROUPS_H
#define SKALIBS_SETGROUPS_H

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSETGROUPS

#include <unistd.h>

extern int setgroups_with_egid (size_t, gid_t const *) ;
extern int skalibs_setgroups (size_t, gid_t const *) ;

#else

#include <errno.h>
#define setgroups(n, tab) (errno = ENOSYS, -1)
#define setgroups_with_egid(n, tab) (errno = ENOSYS, -1)
#define skalibs_setgroups(n, tab) (errno = ENOSYS, -1)

#endif

#endif
