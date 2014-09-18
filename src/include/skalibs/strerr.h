/* ISC license. */

#ifndef STRERR_H
#define STRERR_H

#include <skalibs/gccattributes.h>

extern void strerr_warn (char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_die (int, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_warnsys (char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_diesys (int, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;

#define strerr_warn10(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, se) \
strerr_warn(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, se)
#define strerr_warn9(x1, x2, x3, x4, x5, x6, x7, x8, x9, se) \
strerr_warn(x1, x2, x3, x4, x5, x6, x7, x8, x9, 0, se)
#define strerr_warn8(x1, x2, x3, x4, x5, x6, x7, x8, se) \
strerr_warn(x1, x2, x3, x4, x5, x6, x7, x8, 0, 0, se)
#define strerr_warn7(x1, x2, x3, x4, x5, x6, x7, se) \
strerr_warn(x1, x2, x3, x4, x5, x6, x7, 0, 0, 0, se)
#define strerr_warn6(x1, x2, x3, x4, x5, x6, se) \
strerr_warn(x1, x2, x3, x4, x5, x6, 0, 0, 0, 0, se)
#define strerr_warn5(x1, x2, x3, x4, x5, se) \
strerr_warn(x1, x2, x3, x4, x5, 0, 0, 0, 0, 0, se)
#define strerr_warn4(x1, x2, x3, x4, se) \
strerr_warn(x1, x2, x3, x4, 0, 0, 0, 0, 0, 0, se)
#define strerr_warn3(x1, x2, x3, se) \
strerr_warn(x1, x2, x3, 0, 0, 0, 0, 0, 0, 0, se)
#define strerr_warn2(x1, x2, se) \
strerr_warn(x1, x2, 0, 0, 0, 0, 0, 0, 0, 0, se)
#define strerr_warn1(x1, se) \
strerr_warn(x1, 0, 0, 0, 0, 0, 0, 0, 0, 0, se)

#define strerr_warn10sys(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) \
strerr_warnsys(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10)
#define strerr_warn9sys(x1, x2, x3, x4, x5, x6, x7, x8, x9) \
strerr_warnsys(x1, x2, x3, x4, x5, x6, x7, x8, (x9), 0)
#define strerr_warn8sys(x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_warnsys(x1, x2, x3, x4, x5, x6, x7, (x8), 0, 0)
#define strerr_warn7sys(x1, x2, x3, x4, x5, x6, x7) \
strerr_warnsys(x1, x2, x3, x4, x5, x6, (x7), 0, 0, 0)
#define strerr_warn6sys(x1, x2, x3, x4, x5, x6) \
strerr_warnsys(x1, x2, x3, x4, x5, (x6), 0, 0, 0, 0)
#define strerr_warn5sys(x1, x2, x3, x4, x5) \
strerr_warnsys(x1, x2, x3, x4, (x5), 0, 0, 0, 0, 0)
#define strerr_warn4sys(x1, x2, x3, x4) \
strerr_warnsys(x1, x2, x3, (x4), 0, 0, 0, 0, 0, 0)
#define strerr_warn3sys(x1, x2, x3) \
strerr_warnsys(x1, x2, (x3), 0, 0, 0, 0, 0, 0, 0)
#define strerr_warn2sys(x1, x2) \
strerr_warnsys(x1, (x2), 0, 0, 0, 0, 0, 0, 0, 0)
#define strerr_warn1sys(x1) \
strerr_warnsys((x1), 0, 0, 0, 0, 0, 0, 0, 0, 0)

#define strerr_warn10x(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) \
strerr_warn(x1, x2, x3, x4, x5, x6, x7, x8, x9, (x10), 0)
#define strerr_warn9x(x1, x2, x3, x4, x5, x6, x7, x8, x9) \
strerr_warn(x1, x2, x3, x4, x5, x6, x7, x8, (x9), 0, 0)
#define strerr_warn8x(x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_warn(x1, x2, x3, x4, x5, x6, x7, (x8), 0, 0, 0)
#define strerr_warn7x(x1, x2, x3, x4, x5, x6, x7) \
strerr_warn(x1, x2, x3, x4, x5, x6, (x7), 0, 0, 0, 0)
#define strerr_warn6x(x1, x2, x3, x4, x5, x6) \
strerr_warn(x1, x2, x3, x4, x5, (x6), 0, 0, 0, 0, 0)
#define strerr_warn5x(x1, x2, x3, x4, x5) \
strerr_warn(x1, x2, x3, x4, (x5), 0, 0, 0, 0, 0, 0)
#define strerr_warn4x(x1, x2, x3, x4) \
strerr_warn(x1, x2, x3, (x4), 0, 0, 0, 0, 0, 0, 0)
#define strerr_warn3x(x1, x2, x3) \
strerr_warn(x1, x2, (x3), 0, 0, 0, 0, 0, 0, 0, 0)
#define strerr_warn2x(x1, x2) \
strerr_warn(x1, (x2), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define strerr_warn1x(x1) \
strerr_warn((x1), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

#define strerr_die10(e, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, se) \
strerr_die(e, x1, x2, x3, x4, x5 , x6, x7, x8, x9, x10, se)
#define strerr_die9(e, x1, x2, x3, x4, x5, x6, x7, x8, x9, se) \
strerr_die(e, x1, x2, x3, x4, x5, x6, x7, x8, x9, 0, se)
#define strerr_die8(e, x1, x2, x3, x4, x5, x6, x7, x8, se) \
strerr_die(e, x1, x2, x3, x4, x5, x6, x7, x8, 0, 0, se)
#define strerr_die7(e, x1, x2, x3, x4, x5, x6, x7, se) \
strerr_die(e, x1, x2, x3, x4, x5, x6, x7, 0, 0, 0, se)
#define strerr_die6(e, x1, x2, x3, x4, x5, x6, se) \
strerr_die(e, x1, x2, x3, x4, x5, x6, 0, 0, 0, 0, se)
#define strerr_die5(e, x1, x2, x3, x4, x5, se) \
strerr_die(e, x1, x2, x3, x4, x5, 0, 0, 0, 0, 0, se)
#define strerr_die4(e, x1, x2, x3, x4, se) \
strerr_die(e, x1, x2, x3, x4, 0, 0, 0, 0, 0, 0, se)
#define strerr_die3(e, x1, x2, x3, se) \
strerr_die(e, x1, x2, x3, 0, 0, 0, 0, 0, 0, 0, se)
#define strerr_die2(e, x1, x2, se) \
strerr_die(e, x1, x2, 0, 0, 0, 0, 0, 0, 0, 0, se)
#define strerr_die1(e, x1, se) \
strerr_die(e, x1, 0, 0, 0, 0, 0, 0, 0, 0, 0, se)

#define strerr_die10sys(e, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) \
strerr_diesys(e, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10)
#define strerr_die9sys(e, x1, x2, x3, x4, x5, x6, x7, x8, x9) \
strerr_diesys(e, x1, x2, x3, x4, x5, x6, x7, x8, (x9), 0)
#define strerr_die8sys(e, x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_diesys(e, x1, x2, x3, x4, x5, x6, x7, (x8), 0, 0)
#define strerr_die7sys(e, x1, x2, x3, x4, x5, x6, x7) \
strerr_diesys(e, x1, x2, x3, x4, x5, x6, (x7), 0, 0, 0)
#define strerr_die6sys(e, x1, x2, x3, x4, x5, x6) \
strerr_diesys(e, x1, x2, x3, x4, x5, (x6), 0, 0, 0, 0)
#define strerr_die5sys(e, x1, x2, x3, x4, x5) \
strerr_diesys(e, x1, x2, x3, x4, (x5), 0, 0, 0, 0, 0)
#define strerr_die4sys(e, x1, x2, x3, x4) \
strerr_diesys(e, x1, x2, x3, (x4), 0, 0, 0, 0, 0, 0)
#define strerr_die3sys(e, x1, x2, x3) \
strerr_diesys(e, x1, x2, (x3), 0, 0, 0, 0, 0, 0, 0)
#define strerr_die2sys(e, x1, x2) \
strerr_diesys(e, x1, (x2), 0, 0, 0, 0, 0, 0, 0, 0)
#define strerr_die1sys(e, x1) \
strerr_diesys(e, (x1), 0, 0, 0, 0, 0, 0, 0, 0, 0)

#define strerr_die10x(e, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) \
strerr_die(e, x1, x2, x3, x4, x5, x6, x7, x8, x9, (x10), 0)
#define strerr_die9x(e, x1, x2, x3, x4, x5, x6, x7, x8, x9) \
strerr_die(e, x1, x2, x3, x4, x5, x6, x7, x8, (x9), 0, 0)
#define strerr_die8x(e, x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_die(e, x1, x2, x3, x4, x5, x6, x7, (x8), 0, 0, 0)
#define strerr_die7x(e, x1, x2, x3, x4, x5, x6, x7) \
strerr_die(e, x1, x2, x3, x4, x5, x6, (x7), 0, 0, 0, 0)
#define strerr_die6x(e, x1, x2, x3, x4, x5, x6) \
strerr_die(e, x1, x2, x3, x4, x5, (x6), 0, 0, 0, 0, 0)
#define strerr_die5x(e, x1, x2, x3, x4, x5) \
strerr_die(e, x1, x2, x3, x4, (x5), 0, 0, 0, 0, 0, 0)
#define strerr_die4x(e, x1, x2, x3, x4) \
strerr_die(e, x1, x2, x3, (x4), 0, 0, 0, 0, 0, 0, 0)
#define strerr_die3x(e, x1, x2, x3) \
strerr_die(e, x1, x2, (x3), 0, 0, 0, 0, 0, 0, 0, 0)
#define strerr_die2x(e, x1, x2) \
strerr_die(e, x1, (x2), 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define strerr_die1x(e, x1) \
strerr_die(e, (x1), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

#endif
