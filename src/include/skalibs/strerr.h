/* ISC license. */

#ifndef SKALIBS_STRERR_H
#define SKALIBS_STRERR_H

#include <skalibs/gccattributes.h>

extern void strerr_warnv (char const *const *, unsigned int) ;
extern void strerr_warnvsys (char const *const *, unsigned int) ;
extern void strerr_diev (int, char const *const *, unsigned int) gccattr_noreturn ;
extern void strerr_dievsys(int, char const *const *, unsigned int) gccattr_noreturn ;

extern void strerr_warnl (unsigned int, ...) ;
extern void strerr_warnlsys (unsigned int, ...) ;
extern void strerr_diel (int, unsigned int, ...) gccattr_noreturn ;
extern void strerr_dielsys (int, unsigned int, ...) gccattr_noreturn ;

extern void strerr_warn1x (char const *) ;
extern void strerr_warn2x (char const *, char const *) ;
extern void strerr_warn3x (char const *, char const *, char const *) ;
extern void strerr_warn4x (char const *, char const *, char const *, char const *) ;
extern void strerr_warn5x (char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_warn6x (char const *, char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_warn7x (char const *, char const *, char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_warn8x (char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_warn9x (char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_warn10x (char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_warn11x (char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) ;

extern void strerr_warn1sys (char const *) ;
extern void strerr_warn2sys (char const *, char const *) ;
extern void strerr_warn3sys (char const *, char const *, char const *) ;
extern void strerr_warn4sys (char const *, char const *, char const *, char const *) ;
extern void strerr_warn5sys (char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_warn6sys (char const *, char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_warn7sys (char const *, char const *, char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_warn8sys (char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_warn9sys (char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_warn10sys (char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) ;
extern void strerr_warn11sys (char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) ;

extern void strerr_die1x (int, char const *) gccattr_noreturn ;
extern void strerr_die2x (int, char const *, char const *) gccattr_noreturn ;
extern void strerr_die3x (int, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die4x (int, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die5x (int, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die6x (int, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die7x (int, char const *, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die8x (int, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die9x (int, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die10x (int, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die11x (int, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;

extern void strerr_die1sys (int, char const *) gccattr_noreturn ;
extern void strerr_die2sys (int, char const *, char const *) gccattr_noreturn ;
extern void strerr_die3sys (int, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die4sys (int, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die5sys (int, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die6sys (int, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die7sys (int, char const *, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die8sys (int, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die9sys (int, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die10sys (int, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;
extern void strerr_die11sys (int, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *, char const *) gccattr_noreturn ;

extern char const *PROG ;

#define strerr_warnw1x(x1) \
strerr_warn3x(PROG, ": warning: ", (x1))
#define strerr_warnw2x(x1, x2) \
strerr_warn4x(PROG, ": warning: ", (x1), x2)
#define strerr_warnw3x(x1, x2, x3) \
strerr_warn5x(PROG, ": warning: ", (x1), x2, x3)
#define strerr_warnw4x(x1, x2, x3, x4) \
strerr_warn6x(PROG, ": warning: ", (x1), x2, x3, x4)
#define strerr_warnw5x(x1, x2, x3, x4, x5) \
strerr_warn7x(PROG, ": warning: ", (x1), x2, x3, x4, x5)
#define strerr_warnw6x(x1, x2, x3, x4, x5, x6) \
strerr_warn8x(PROG, ": warning: ", (x1), x2, x3, x4, x5, x6)
#define strerr_warnw7x(x1, x2, x3, x4, x5, x6, x7) \
strerr_warn9x(PROG, ": warning: ", (x1), x2, x3, x4, x5, x6, x7)
#define strerr_warnw8x(x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_warn10x(PROG, ": warning: ", (x1), x2, x3, x4, x5, x6, x7, x8)
#define strerr_warnw9x(x1, x2, x3, x4, x5, x6, x7, x8, x9) \
strerr_warn11x(PROG, ": warning: ", (x1), x2, x3, x4, x5, x6, x7, x8, x9)

#define strerr_warnw1sys(x1) \
strerr_warn3sys(PROG, ": warning: ", (x1))
#define strerr_warnw2sys(x1, x2) \
strerr_warn4sys(PROG, ": warning: ", (x1), x2)
#define strerr_warnw3sys(x1, x2, x3) \
strerr_warn5sys(PROG, ": warning: ", (x1), x2, x3)
#define strerr_warnw4sys(x1, x2, x3, x4) \
strerr_warn6sys(PROG, ": warning: ", (x1), x2, x3, x4)
#define strerr_warnw5sys(x1, x2, x3, x4, x5) \
strerr_warn7sys(PROG, ": warning: ", (x1), x2, x3, x4, x5)
#define strerr_warnw6sys(x1, x2, x3, x4, x5, x6) \
strerr_warn8sys(PROG, ": warning: ", (x1), x2, x3, x4, x5, x6)
#define strerr_warnw7sys(x1, x2, x3, x4, x5, x6, x7) \
strerr_warn9sys(PROG, ": warning: ", (x1), x2, x3, x4, x5, x6, x7)
#define strerr_warnw8sys(x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_warn10sys(PROG, ": warning: ", (x1), x2, x3, x4, x5, x6, x7, x8)
#define strerr_warnw9sys(x1, x2, x3, x4, x5, x6, x7, x8, x9) \
strerr_warn11sys(PROG, ": warning: ", (x1), x2, x3, x4, x5, x6, x7, x8, x9)

#define strerr_diew1x(e, x1) \
strerr_die3x(e, PROG, ": warning: ", x1)
#define strerr_diew2x(e, x1, x2) \
strerr_die4x(e, PROG, ": warning: ", x1, x2)
#define strerr_diew3x(e, x1, x2, x3) \
strerr_die5x(e, PROG, ": warning: ", x1, x2, x3)
#define strerr_diew4x(e, x1, x2, x3, x4) \
strerr_die6x(e, PROG, ": warning: ", x1, x2, x3, x4)
#define strerr_diew5x(e, x1, x2, x3, x4, x5) \
strerr_die7x(e, PROG, ": warning: ", x1, x2, x3, x4, x5)
#define strerr_diew6x(e, x1, x2, x3, x4, x5, x6) \
strerr_die8x(e, PROG, ": warning: ", x1, x2, x3, x4, x5, x6)
#define strerr_diew7x(e, x1, x2, x3, x4, x5, x6, x7) \
strerr_die9x(e, PROG, ": warning: ", x1, x2, x3, x4, x5, x6, x7)
#define strerr_diew8x(e, x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_die10x(e, PROG, ": warning: ", x1, x2, x3, x4, x5, x6, x7, x8)
#define strerr_diew9x(e, x1, x2, x3, x4, x5, x6, x7, x8, x9) \
strerr_die11x(e, PROG, ": warning: ", x1, x2, x3, x4, x5, x6, x7, x8, x9)

#define strerr_diew1sys(e, x1) \
strerr_die3sys(e, PROG, ": warning: ", (x1))
#define strerr_diew2sys(e, x1, x2) \
strerr_die4sys(e, PROG, ": warning: ", x1, x2)
#define strerr_diew3sys(e, x1, x2, x3) \
strerr_die5sys(e, PROG, ": warning: ", x1, x2, x3)
#define strerr_diew4sys(e, x1, x2, x3, x4) \
strerr_die6sys(e, PROG, ": warning: ", x1, x2, x3, x4)
#define strerr_diew5sys(e, x1, x2, x3, x4, x5) \
strerr_die7sys(e, PROG, ": warning: ", x1, x2, x3, x4, x5)
#define strerr_diew6sys(e, x1, x2, x3, x4, x5, x6) \
strerr_die8sys(e, PROG, ": warning: ", x1, x2, x3, x4, x5, x6)
#define strerr_diew7sys(e, x1, x2, x3, x4, x5, x6, x7) \
strerr_die9sys(e, PROG, ": warning: ", x1, x2, x3, x4, x5, x6, x7)
#define strerr_diew8sys(e, x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_die10sys(e, PROG, ": warning: ", x1, x2, x3, x4, x5, x6, x7, x8)
#define strerr_diew9sys(e, x1, x2, x3, x4, x5, x6, x7, x8, x9) \
strerr_die11sys(e, PROG, ": warning: ", x1, x2, x3, x4, x5, x6, x7, x8, x9)

#define strerr_dief1x(e, x1) \
strerr_die3x(e, PROG, ": fatal: ", x1)
#define strerr_dief2x(e, x1, x2) \
strerr_die4x(e, PROG, ": fatal: ", x1, x2)
#define strerr_dief3x(e, x1, x2, x3) \
strerr_die5x(e, PROG, ": fatal: ", x1, x2, x3)
#define strerr_dief4x(e, x1, x2, x3, x4) \
strerr_die6x(e, PROG, ": fatal: ", x1, x2, x3, x4)
#define strerr_dief5x(e, x1, x2, x3, x4, x5) \
strerr_die7x(e, PROG, ": fatal: ", x1, x2, x3, x4, x5)
#define strerr_dief6x(e, x1, x2, x3, x4, x5, x6) \
strerr_die8x(e, PROG, ": fatal: ", x1, x2, x3, x4, x5, x6)
#define strerr_dief7x(e, x1, x2, x3, x4, x5, x6, x7) \
strerr_die9x(e, PROG, ": fatal: ", x1, x2, x3, x4, x5, x6, x7)
#define strerr_dief8x(e, x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_die10x(e, PROG, ": fatal: ", x1, x2, x3, x4, x5, x6, x7, x8)

#define strerr_dief1sys(e, x1) \
strerr_die3sys(e, PROG, ": fatal: ", x1)
#define strerr_dief2sys(e, x1, x2) \
strerr_die4sys(e, PROG, ": fatal: ", x1, x2)
#define strerr_dief3sys(e, x1, x2, x3) \
strerr_die5sys(e, PROG, ": fatal: ", x1, x2, x3)
#define strerr_dief4sys(e, x1, x2, x3, x4) \
strerr_die6sys(e, PROG, ": fatal: ", x1, x2, x3, x4)
#define strerr_dief5sys(e, x1, x2, x3, x4, x5) \
strerr_die7sys(e, PROG, ": fatal: ", x1, x2, x3, x4, x5)
#define strerr_dief6sys(e, x1, x2, x3, x4, x5, x6) \
strerr_die8sys(e, PROG, ": fatal: ", x1, x2, x3, x4, x5, x6)
#define strerr_dief7sys(e, x1, x2, x3, x4, x5, x6, x7) \
strerr_die9sys(e, PROG, ": fatal: ", x1, x2, x3, x4, x5, x6, x7)
#define strerr_dief8sys(e, x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_die10sys(e, PROG, ": fatal: ", x1, x2, x3, x4, x5, x6, x7, x8)
#define strerr_dief9sys(e, x1, x2, x3, x4, x5, x6, x7, x8, x9) \
strerr_die11sys(e, PROG, ": fatal: ", x1, x2, x3, x4, x5, x6, x7, x8, x9)

#define strerr_diefu1x(e, x1) \
strerr_die4x(e, PROG, ": fatal: ", "unable to ", x1)
#define strerr_diefu2x(e, x1, x2) \
strerr_die5x(e, PROG, ": fatal: ", "unable to ", x1, x2)
#define strerr_diefu3x(e, x1, x2, x3) \
strerr_die6x(e, PROG, ": fatal: ", "unable to ", x1, x2, x3)
#define strerr_diefu4x(e, x1, x2, x3, x4) \
strerr_die7x(e, PROG, ": fatal: ", "unable to ", x1, x2, x3, x4)
#define strerr_diefu5x(e, x1, x2, x3, x4, x5) \
strerr_die8x(e, PROG, ": fatal: ", "unable to ", x1, x2, x3, x4, x5)
#define strerr_diefu6x(e, x1, x2, x3, x4, x5, x6) \
strerr_die9x(e, PROG, ": fatal: ", "unable to ", x1, x2, x3, x4, x5, x6)
#define strerr_diefu7x(e, x1, x2, x3, x4, x5, x6, x7) \
strerr_die10x(e, PROG, ": fatal: ", "unable to ", x1, x2, x3, x4, x5, x6, x7)
#define strerr_diefu8x(e, x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_die11x(e, PROG, ": fatal: ", "unable to ", x1, x2, x3, x4, x5, x6, x7, x8)

#define strerr_diefu1sys(e, x1) \
strerr_die4sys(e, PROG, ": fatal: ", "unable to ", x1)
#define strerr_diefu2sys(e, x1, x2) \
strerr_die5sys(e, PROG, ": fatal: ", "unable to ", x1, x2)
#define strerr_diefu3sys(e, x1, x2, x3) \
strerr_die6sys(e, PROG, ": fatal: ", "unable to ", x1, x2, x3)
#define strerr_diefu4sys(e, x1, x2, x3, x4) \
strerr_die7sys(e, PROG, ": fatal: ", "unable to ", x1, x2, x3, x4)
#define strerr_diefu5sys(e, x1, x2, x3, x4, x5) \
strerr_die8sys(e, PROG, ": fatal: ", "unable to ", x1, x2, x3, x4, x5)
#define strerr_diefu6sys(e, x1, x2, x3, x4, x5, x6) \
strerr_die9sys(e, PROG, ": fatal: ", "unable to ", x1, x2, x3, x4, x5, x6)
#define strerr_diefu7sys(e, x1, x2, x3, x4, x5, x6, x7) \
strerr_die10sys(e, PROG, ": fatal: ", "unable to ", x1, x2, x3, x4, x5, x6, x7)
#define strerr_diefu8sys(e, x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_die11sys(e, PROG, ": fatal: ", "unable to ", x1, x2, x3, x4, x5, x6, x7, x8)

#define strerr_warnwu1x(x1) \
strerr_warn4x(PROG, ": warning: ", "unable to ", (x1))
#define strerr_warnwu2x(x1, x2) \
strerr_warn5x(PROG, ": warning: ", "unable to ", (x1), x2)
#define strerr_warnwu3x(x1, x2, x3) \
strerr_warn6x(PROG, ": warning: ", "unable to ", (x1), x2, x3)
#define strerr_warnwu4x(x1, x2, x3, x4) \
strerr_warn7x(PROG, ": warning: ", "unable to ", (x1), x2, x3, x4)
#define strerr_warnwu5x(x1, x2, x3, x4, x5) \
strerr_warn8x(PROG, ": warning: ", "unable to ", (x1), x2, x3, x4, x5)
#define strerr_warnwu6x(x1, x2, x3, x4, x5, x6) \
strerr_warn9x(PROG, ": warning: ", "unable to ", (x1), x2, x3, x4, x5, x6)
#define strerr_warnwu7x(x1, x2, x3, x4, x5, x6, x7) \
strerr_warn10x(PROG, ": warning: ", "unable to ", (x1), x2, x3, x4, x5, x6, x7)

#define strerr_warnwu1sys(x1) \
strerr_warn4sys(PROG, ": warning: ", "unable to ", (x1))
#define strerr_warnwu2sys(x1, x2) \
strerr_warn5sys(PROG, ": warning: ", "unable to ", (x1), x2)
#define strerr_warnwu3sys(x1, x2, x3) \
strerr_warn6sys(PROG, ": warning: ", "unable to ", (x1), x2, x3)
#define strerr_warnwu4sys(x1, x2, x3, x4) \
strerr_warn7sys(PROG, ": warning: ", "unable to ", (x1), x2, x3, x4)
#define strerr_warnwu5sys(x1, x2, x3, x4, x5) \
strerr_warn8sys(PROG, ": warning: ", "unable to ", (x1), x2, x3, x4, x5)
#define strerr_warnwu6sys(x1, x2, x3, x4, x5, x6) \
strerr_warn9sys(PROG, ": warning: ", "unable to ", (x1), x2, x3, x4, x5, x6)
#define strerr_warnwu7sys(x1, x2, x3, x4, x5, x6, x7) \
strerr_warn10sys(PROG, ": warning: ", "unable to ", (x1), x2, x3, x4, x5, x6, x7)
#define strerr_warnwu8sys(x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_warn11sys(PROG, ": warning: ", "unable to ", (x1), x2, x3, x4, x5, x6, x7, x8)

#define strerr_diewu1x(e, x1) \
strerr_die4x(e, PROG, ": warning: ", "unable to ", x1)
#define strerr_diewu2x(e, x1, x2) \
strerr_die5x(e, PROG, ": warning: ", "unable to ", x1, x2)
#define strerr_diewu3x(e, x1, x2, x3) \
strerr_die6x(e, PROG, ": warning: ", "unable to ", x1, x2, x3)
#define strerr_diewu4x(e, x1, x2, x3, x4) \
strerr_die7x(e, PROG, ": warning: ", "unable to ", x1, x2, x3, x4)
#define strerr_diewu5x(e, x1, x2, x3, x4, x5) \
strerr_die8x(e, PROG, ": warning: ", "unable to ", x1, x2, x3, x4, x5)
#define strerr_diewu6x(e, x1, x2, x3, x4, x5, x6) \
strerr_die9x(e, PROG, ": warning: ", "unable to ", x1, x2, x3, x4, x5, x6)
#define strerr_diewu7x(e, x1, x2, x3, x4, x5, x6, x7) \
strerr_die10x(e, PROG, ": warning: ", "unable to ", x1, x2, x3, x4, x5, x6, x7)
#define strerr_diewu8x(e, x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_die11x(e, PROG, ": warning: ", "unable to ", x1, x2, x3, x4, x5, x6, x7, x8)

#define strerr_diewu1sys(e, x1) \
strerr_die4sys(e, PROG, ": warning: ", "unable to ", (x1))
#define strerr_diewu2sys(e, x1, x2) \
strerr_die5sys(e, PROG, ": warning: ", "unable to ", x1, x2)
#define strerr_diewu3sys(e, x1, x2, x3) \
strerr_die6sys(e, PROG, ": warning: ", "unable to ", x1, x2, x3)
#define strerr_diewu4sys(e, x1, x2, x3, x4) \
strerr_die7sys(e, PROG, ": warning: ", "unable to ", x1, x2, x3, x4)
#define strerr_diewu5sys(e, x1, x2, x3, x4, x5) \
strerr_die8sys(e, PROG, ": warning: ", "unable to ", x1, x2, x3, x4, x5)
#define strerr_diewu6sys(e, x1, x2, x3, x4, x5, x6) \
strerr_die9sys(e, PROG, ": warning: ", "unable to ", x1, x2, x3, x4, x5, x6)
#define strerr_diewu7sys(e, x1, x2, x3, x4, x5, x6, x7) \
strerr_die10sys(e, PROG, ": warning: ", "unable to ", x1, x2, x3, x4, x5, x6, x7)
#define strerr_diewu8sys(e, x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_die11sys(e, PROG, ": warning: ", "unable to ", x1, x2, x3, x4, x5, x6, x7, x8)

#define strerr_dieusage(e, u) \
strerr_die3x(e, PROG, ": usage: ", u)

#define strerr_dienotset(e, x) \
strerr_dief2x(e, (x), " not set")

#define strerr_dieinvalid(e, x) \
strerr_dief2x(e, "invalid $", x)

#define strerr_dieexec(e, x) \
strerr_diefu2sys(e, "exec ", x)

#define strerr_warni1x(x1) \
strerr_warn3x(PROG, ": info: ", (x1))
#define strerr_warni2x(x1, x2) \
strerr_warn4x(PROG, ": info: ", (x1), x2)
#define strerr_warni3x(x1, x2, x3) \
strerr_warn5x(PROG, ": info: ", (x1), x2, x3)
#define strerr_warni4x(x1, x2, x3, x4) \
strerr_warn6x(PROG, ": info: ", (x1), x2, x3, x4)
#define strerr_warni5x(x1, x2, x3, x4, x5) \
strerr_warn7x(PROG, ": info: ", (x1), x2, x3, x4, x5)
#define strerr_warni6x(x1, x2, x3, x4, x5, x6) \
strerr_warn8x(PROG, ": info: ", (x1), x2, x3, x4, x5, x6)
#define strerr_warni7x(x1, x2, x3, x4, x5, x6, x7) \
strerr_warn9x(PROG, ": info: ", (x1), x2, x3, x4, x5, x6, x7)
#define strerr_warni8x(x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_warn10x(PROG, ": info: ", (x1), x2, x3, x4, x5, x6, x7, x8)
#define strerr_warni9x(x1, x2, x3, x4, x5, x6, x7, x8, x9) \
strerr_warn11x(PROG, ": info: ", (x1), x2, x3, x4, x5, x6, x7, x8, x9)

#define strerr_warni1sys(x1) \
strerr_warn3sys(PROG, ": info: ", (x1))
#define strerr_warni2sys(x1, x2) \
strerr_warn4sys(PROG, ": info: ", (x1), x2)
#define strerr_warni3sys(x1, x2, x3) \
strerr_warn5sys(PROG, ": info: ", (x1), x2, x3)
#define strerr_warni4sys(x1, x2, x3, x4) \
strerr_warn6sys(PROG, ": info: ", (x1), x2, x3, x4)
#define strerr_warni5sys(x1, x2, x3, x4, x5) \
strerr_warn7sys(PROG, ": info: ", (x1), x2, x3, x4, x5)
#define strerr_warni6sys(x1, x2, x3, x4, x5, x6) \
strerr_warn8sys(PROG, ": info: ", (x1), x2, x3, x4, x5, x6)
#define strerr_warni7sys(x1, x2, x3, x4, x5, x6, x7) \
strerr_warn9sys(PROG, ": info: ", (x1), x2, x3, x4, x5, x6, x7)
#define strerr_warni8sys(x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_warn10sys(PROG, ": info: ", (x1), x2, x3, x4, x5, x6, x7, x8)
#define strerr_warni9sys(x1, x2, x3, x4, x5, x6, x7, x8, x9) \
strerr_warn11sys(PROG, ": info: ", (x1), x2, x3, x4, x5, x6, x7, x8, x9)

#define strerr_warnt1x(x1) \
strerr_warn3x(PROG, ": tracing: ", (x1))
#define strerr_warnt2x(x1, x2) \
strerr_warn4x(PROG, ": tracing: ", (x1), x2)
#define strerr_warnt3x(x1, x2, x3) \
strerr_warn5x(PROG, ": tracing: ", (x1), x2, x3)
#define strerr_warnt4x(x1, x2, x3, x4) \
strerr_warn6x(PROG, ": tracing: ", (x1), x2, x3, x4)
#define strerr_warnt5x(x1, x2, x3, x4, x5) \
strerr_warn7x(PROG, ": tracing: ", (x1), x2, x3, x4, x5)
#define strerr_warnt6x(x1, x2, x3, x4, x5, x6) \
strerr_warn8x(PROG, ": tracing: ", (x1), x2, x3, x4, x5, x6)
#define strerr_warnt7x(x1, x2, x3, x4, x5, x6, x7) \
strerr_warn9x(PROG, ": tracing: ", (x1), x2, x3, x4, x5, x6, x7)
#define strerr_warnt8x(x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_warn10x(PROG, ": tracing: ", (x1), x2, x3, x4, x5, x6, x7, x8)
#define strerr_warnt9x(x1, x2, x3, x4, x5, x6, x7, x8, x9) \
strerr_warn11x(PROG, ": tracing: ", (x1), x2, x3, x4, x5, x6, x7, x8, x9)

#define strerr_warnt1sys(x1) \
strerr_warn3sys(PROG, ": tracing: ", (x1))
#define strerr_warnt2sys(x1, x2) \
strerr_warn4sys(PROG, ": tracing: ", (x1), x2)
#define strerr_warnt3sys(x1, x2, x3) \
strerr_warn5sys(PROG, ": tracing: ", (x1), x2, x3)
#define strerr_warnt4sys(x1, x2, x3, x4) \
strerr_warn6sys(PROG, ": tracing: ", (x1), x2, x3, x4)
#define strerr_warnt5sys(x1, x2, x3, x4, x5) \
strerr_warn7sys(PROG, ": tracing: ", (x1), x2, x3, x4, x5)
#define strerr_warnt6sys(x1, x2, x3, x4, x5, x6) \
strerr_warn8sys(PROG, ": tracing: ", (x1), x2, x3, x4, x5, x6)
#define strerr_warnt7sys(x1, x2, x3, x4, x5, x6, x7) \
strerr_warn9sys(PROG, ": tracing: ", (x1), x2, x3, x4, x5, x6, x7)
#define strerr_warnt8sys(x1, x2, x3, x4, x5, x6, x7, x8) \
strerr_warn10sys(PROG, ": tracing: ", (x1), x2, x3, x4, x5, x6, x7, x8)
#define strerr_warnt9sys(x1, x2, x3, x4, x5, x6, x7, x8, x9) \
strerr_warn11sys(PROG, ": tracing: ", (x1), x2, x3, x4, x5, x6, x7, x8, x9)

#endif
