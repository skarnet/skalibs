/* ISC license. */

#ifndef SKALIBS_POSIXPLZ_H
#define SKALIBS_POSIXPLZ_H

#include <sys/types.h>
#include <sys/stat.h>
#include <regex.h>

#include <skalibs/gccattributes.h>
#include <skalibs/functypes.h>


 /*
    Stuff that doesn't have its own POSIX header for some reason.
 */

extern char **environ ;


 /*
    Non-POSIX functions that some OSes provide and others don't.
    setgroups() isn't included because it's its own kind of broken.
 */

extern void *memmem (void const *, size_t, void const *, size_t) gccattr_pure ;
extern char *strcasestr (char const *, char const *) gccattr_pure ;
extern int getpeereid (int, uid_t *, gid_t *) ;


 /*
    Functions that aren't standard at all, but honestly could be. :P
 */

extern void execvep (char const *, char const *const *, char const *const *, char const *) ;
extern void execvep_loose (char const *, char const *const *, char const *const *, char const *) ;
extern void unlink_void (char const *) ;
extern void munmap_void (void *, size_t) ;
extern pid_t doublefork (void) ;
extern int touch (char const *) ;

extern int mkfiletemp (char *, create_func_ref, mode_t, void *) ;
extern int mklinktemp (char const *, char *, link_func_ref) ;
extern int mkptemp (char *) ;
extern int mkptemp2 (char *, unsigned int) ;
extern int mkltemp (char const *, char *) ;
extern int mkhtemp (char const *, char *) ;
extern int mkctemp (char *, mode_t, dev_t) ;
extern int mkbtemp (char *, mode_t, dev_t) ;


 /*
    Wrappers around functions that should be specified better.
 */

#define skalibs_regcomp(re, s, flags) regcomp(re, (s)[0] ? (s) : ".*", flags)

#endif
