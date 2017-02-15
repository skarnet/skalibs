/* ISC license. */

#ifndef BYTESTR_H
#define BYTESTR_H

#include <skalibs/config.h>
#include <skalibs/gccattributes.h>

/* for Alphas and other archs where char != 8bit */
#define T8(x)   ((x) & 0xffU)

#include <skalibs/sysdeps.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <skalibs/uint64.h>

#define byte_copy(to, n, from) memmove(to, (from), n)
#define byte_copyr(to, n, from) memmove(to, (from), n)
#define byte_diff(a, n, b) memcmp(a, (b), n)
#define byte_zero(p, n) memset(p, 0, n)
#define str_len strlen

#ifdef SKALIBS_HASSTRNLEN
# define str_nlen strnlen
#else
# define str_nlen(s, max) byte_chr(s, (max), 0)
#endif

#define str_diff strcmp
#define str_diffn strncmp
#define str_copy(to, from) strlen(strcpy(to, from))
#define case_diffs strcasecmp
#define case_diffn strncasecmp

extern size_t byte_chr (char const *, size_t, int) gccattr_pure ;
extern size_t byte_rchr (char const *, size_t, int) gccattr_pure ;
extern size_t byte_in (char const *, size_t, char const *, size_t) gccattr_pure ;
#define byte_equal(s, n, t) (!byte_diff((s), (n), (t)))
extern uint64_t byte_count (char const *, size_t, char) gccattr_pure ;

#define str_diffb(a, n, b) str_diffn(a, (b), n)
extern size_t str_chr (char const *, int) gccattr_pure ;
extern size_t str_rchr (char const *, int) gccattr_pure ;
extern int str_start (char const *, char const *) gccattr_pure ;
#define str_equal(s, t) (!str_diff(s, t))
extern size_t str_strn (char const *, size_t, char const *, size_t) gccattr_pure ;

extern void case_lowers (char *) ;
extern void case_lowerb (char *, size_t) ;
extern void case_uppers (char *) ;
extern void case_upperb (char *, size_t) ;
#define case_diffb(a, n, b) case_diffn(a, (b), n)
#define case_equals(a, b) (!case_diffs(a, b))
#define case_equalb(a, n, b) (!case_diffb(a, n, b))
#define case_starts(s, t) case_startb(s, strlen(s), t)
extern int case_startb (char const *, size_t, char const *) gccattr_pure ;
extern size_t case_str (char const *, char const *) gccattr_pure ;

#endif
