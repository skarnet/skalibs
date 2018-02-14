/* ISC license. */

#ifndef SKALIBS_POSIXPLZ_H
#define SKALIBS_POSIXPLZ_H

#include <sys/types.h>
#include <skalibs/gccattributes.h>


 /*
    Stuff that doesn't have its own POSIX header for some reason.
 */

extern char **environ ;


 /*
    Stuff that _is_ POSIX, but some OSes still don't have it.
    openat() et al. should be here, but they're impossible to
    emulate correctly, and I don't want an app using openat()
    to think it has safe POSIX semantics when it doesn't :/
    EPROTO et al. should be here, but ugh ifdef forests.
 */

extern size_t strnlen (char const *, size_t) gccattr_pure ;


 /*
    Non-POSIX functions that some OSes provide and others don't.
    setgroups() isn't included because it's its own kind of broken.
 */

extern void *memmem (void const *, size_t, void const *, size_t) gccattr_pure ;
extern int getpeereid (int, uid_t *, gid_t *) ;


 /*
    Functions that aren't standard at all, but honestly could be. :P
 */

extern void execvep (char const *, char const *const *, char const *const *, char const *) ;
extern void execvep_loose (char const *, char const *const *, char const *const *, char const *) ;
extern pid_t doublefork (void) ;
extern int touch (char const *) ;

#endif
