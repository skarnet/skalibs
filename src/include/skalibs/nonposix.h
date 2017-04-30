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
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif


 /* NetBSD: of course they had to have their own macros. */

#ifndef _NETBSD_SOURCE
#define _NETBSD_SOURCE
#endif
#ifndef _INCOMPLETE_XOPEN_C063
#define _INCOMPLETE_XOPEN_C063
#endif


 /* old versions of BSD: system headers are not self-contained,
      starting with sys/types.h normally always works. */

#include <sys/types.h>

#endif
