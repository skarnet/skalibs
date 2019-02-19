/* ISC license. */

#ifndef NONPOSIX_H
#define NONPOSIX_H


 /* Drop all pretense of standardness: some libc headers are *more*
    broken when you define standard feature test macros than when
    you don't (I'm looking at you, FreeBSD). */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE


 /* Solaris: the socket API is not POSIX unless you enable this */

#ifndef _XPG4_2
#define _XPG4_2
#endif
#ifndef _XPG6
#define _XPG6
#endif


 /* Solaris: for settimeofday() and similar. Notice how you
    have to define by hand a macro with double underscores. */

#ifndef __EXTENSIONS__
#define __EXTENSIONS__
#endif


 /* GNU: most extensions are unavailable unless you enable this */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif


 /* BSD and Linux libcs that are not glibc: _BSD_SOURCE opens up a
    lot of extensions. Of course, glibc insisted on changing to a
    different macro, because coordination and consistency would make
    developers' life too easy. */

#ifdef __GLIBC__
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#else
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#endif


 /* NetBSD: of course they had to have their own macro too. */

#ifndef _NETBSD_SOURCE
#define _NETBSD_SOURCE
#endif
#ifndef _INCOMPLETE_XOPEN_C063
#define _INCOMPLETE_XOPEN_C063
#endif


 /* MacOS: needs this for full SUSv3 conformance. Standards are hard. */

#ifndef _DARWIN_C_SOURCE
#define _DARWIN_C_SOURCE
#endif


 /* old versions of BSD and some broken GNU toolchains:
      system headers are not self-contained,
      starting with sys/types.h normally always works. */

#include <sys/types.h>

#endif
