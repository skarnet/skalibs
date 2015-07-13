/* ISC license. */

#ifndef BYTESTR_H
#define BYTESTR_H

#include <skalibs/config.h>
#include <skalibs/gccattributes.h>

/* for Alphas and other archs where char != 8bit */
#define T8(x)   ((x) & 0xffU)

#ifndef SKALIBS_FLAG_REPLACE_LIBC

#include <skalibs/sysdeps.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>

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

#else

extern void byte_copy (char *, unsigned int, char const *) ;
extern void byte_copyr (char *, unsigned int, char const *) ;
extern int byte_diff (char const *, unsigned int, char const *) gccattr_pure ;
extern void byte_zero (void *, unsigned int) ;
extern unsigned int str_len (char const *) gccattr_pure ;
#define str_nlen(s, max) byte_chr(s, (max), 0)
extern int str_diff (char const *, char const *) gccattr_pure ;
extern int str_diffn (char const *, char const *, unsigned int) gccattr_pure ;
extern unsigned int str_copy (char *, char const *) ;
extern int case_diffs (char const *, char const *) gccattr_pure ;
extern int case_diffn (char const *, char const *, unsigned int) gccattr_pure ;

#endif	

extern unsigned int byte_chr (char const *, unsigned int, int) gccattr_pure ;
extern unsigned int byte_rchr (char const *, unsigned int, int) gccattr_pure ;
extern unsigned int byte_in (char const *, unsigned int, char const *, unsigned int) gccattr_pure ;
#define byte_equal(s, n, t) (!byte_diff((s), (n), (t)))
extern unsigned int byte_count (char const *, unsigned int, char) gccattr_pure ;

#define str_diffb(a, n, b) str_diffn(a, (b), n)
extern unsigned int str_chr (char const *, int) gccattr_pure ;
extern unsigned int str_rchr (char const *, int) gccattr_pure ;
extern int str_start (char const *, char const *) gccattr_pure ;
#define str_equal(s, t) (!str_diff(s, t))
extern unsigned int str_strn (char const *, unsigned int, char const *, unsigned int) gccattr_pure ;

extern void case_lowers (char *) ;
extern void case_lowerb (char *, unsigned int) ;
extern void case_uppers (char *) ;
extern void case_upperb (char *, unsigned int) ;
#define case_diffb(a, n, b) case_diffn(a, (b), n)
#define case_equals(a, b) (!case_diffs(a, b))
#define case_equalb(a, n, b) (!case_diffb(a, n, b))
#define case_starts(s, t) case_startb(s, str_len(s), t)
extern int case_startb (char const *, unsigned int, char const *) gccattr_pure ;
extern unsigned int case_str (char const *, char const *) gccattr_pure ;

#endif
