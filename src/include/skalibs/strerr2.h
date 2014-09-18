/* ISC license. */

#ifndef STRERR2_H
#define STRERR2_H

#include <skalibs/strerr.h>

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

#define strerr_warnw1sys(x1) \
strerr_warn4sys(PROG, ": warning: ", (x1), ": ")
#define strerr_warnw2sys(x1, x2) \
strerr_warn5sys(PROG, ": warning: ", (x1), (x2), ": ")
#define strerr_warnw3sys(x1, x2, x3) \
strerr_warn6sys(PROG, ": warning: ", (x1), x2, (x3), ": ")
#define strerr_warnw4sys(x1, x2, x3, x4) \
strerr_warn7sys(PROG, ": warning: ", (x1), x2, x3, (x4), ": ")
#define strerr_warnw5sys(x1, x2, x3, x4, x5) \
strerr_warn8sys(PROG, ": warning: ", (x1), x2, x3, x4, (x5), ": ")
#define strerr_warnw6sys(x1, x2, x3, x4, x5, x6) \
strerr_warn9sys(PROG, ": warning: ", (x1), x2, x3, x4, x5, (x6), ": ")
#define strerr_warnw7sys(x1, x2, x3, x4, x5, x6, x7) \
strerr_warn10sys(PROG, ": warning: ", (x1), x2, x3, x4, x5, x6, (x7), ": ")

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

#define strerr_diew1sys(e, x1) \
strerr_die4sys(e, PROG, ": warning: ", (x1), ": ")
#define strerr_diew2sys(e, x1, x2) \
strerr_die5sys(e, PROG, ": warning: ", x1, (x2), ": ")
#define strerr_diew3sys(e, x1, x2, x3) \
strerr_die6sys(e, PROG, ": warning: ", x1, x2, (x3), ": ")
#define strerr_diew4sys(e, x1, x2, x3, x4) \
strerr_die7sys(e, PROG, ": warning: ", x1, x2, x3, (x4), ": ")
#define strerr_diew5sys(e, x1, x2, x3, x4, x5) \
strerr_die8sys(e, PROG, ": warning: ", x1, x2, x3, x4, (x5), ": ")
#define strerr_diew6sys(e, x1, x2, x3, x4, x5, x6) \
strerr_die9sys(e, PROG, ": warning: ", x1, x2, x3, x4, x5, (x6), ": ")
#define strerr_diew7sys(e, x1, x2, x3, x4, x5, x6, x7) \
strerr_die10sys(e, PROG, ": warning: ", x1, x2, x3, x4, x5, x6, (x7), ": ")

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
strerr_die4sys(e, PROG, ": fatal: ", (x1), ": ")
#define strerr_dief2sys(e, x1, x2) \
strerr_die5sys(e, PROG, ": fatal: ", x1, (x2), ": ")
#define strerr_dief3sys(e, x1, x2, x3) \
strerr_die6sys(e, PROG, ": fatal: ", x1, x2, (x3), ": ")
#define strerr_dief4sys(e, x1, x2, x3, x4) \
strerr_die7sys(e, PROG, ": fatal: ", x1, x2, x3, (x4), ": ")
#define strerr_dief5sys(e, x1, x2, x3, x4, x5) \
strerr_die8sys(e, PROG, ": fatal: ", x1, x2, x3, x4, (x5), ": ")
#define strerr_dief6sys(e, x1, x2, x3, x4, x5, x6) \
strerr_die9sys(e, PROG, ": fatal: ", x1, x2, x3, x4, x5, (x6), ": ")
#define strerr_dief7sys(e, x1, x2, x3, x4, x5, x6, x7) \
strerr_die10sys(e, PROG, ": fatal: ", x1, x2, x3, x4, x5, x6, (x7), ": ")

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

#define strerr_diefu1sys(e, x1) \
strerr_die5sys(e, PROG, ": fatal: ", "unable to ", (x1), ": ")
#define strerr_diefu2sys(e, x1, x2) \
strerr_die6sys(e, PROG, ": fatal: ", "unable to ", x1, (x2), ": ")
#define strerr_diefu3sys(e, x1, x2, x3) \
strerr_die7sys(e, PROG, ": fatal: ", "unable to ", x1, x2, (x3), ": ")
#define strerr_diefu4sys(e, x1, x2, x3, x4) \
strerr_die8sys(e, PROG, ": fatal: ", "unable to ", x1, x2, x3, (x4), ": ")
#define strerr_diefu5sys(e, x1, x2, x3, x4, x5) \
strerr_die9sys(e, PROG, ": fatal: ", "unable to ", x1, x2, x3, x4, (x5), ": ")
#define strerr_diefu6sys(e, x1, x2, x3, x4, x5, x6) \
strerr_die10sys(e, PROG, ": fatal: ", "unable to ", x1, x2, x3, x4, x5, (x6), ": ")

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
strerr_warn5sys(PROG, ": warning: ", "unable to ", (x1), ": ")
#define strerr_warnwu2sys(x1, x2) \
strerr_warn6sys(PROG, ": warning: ", "unable to ", (x1), (x2), ": ")
#define strerr_warnwu3sys(x1, x2, x3) \
strerr_warn7sys(PROG, ": warning: ", "unable to ", (x1), x2, (x3), ": ")
#define strerr_warnwu4sys(x1, x2, x3, x4) \
strerr_warn8sys(PROG, ": warning: ", "unable to ", (x1), x2, x3, (x4), ": ")
#define strerr_warnwu5sys(x1, x2, x3, x4, x5) \
strerr_warn9sys(PROG, ": warning: ", "unable to ", (x1), x2, x3, x4, (x5), ": ")
#define strerr_warnwu6sys(x1, x2, x3, x4, x5, x6) \
strerr_warn10sys(PROG, ": warning: ", "unable to ", (x1), x2, x3, x4, x5, (x6), ": ")

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

#define strerr_diewu1sys(e, x1) \
strerr_die5sys(e, PROG, ": warning: ", "unable to ", (x1), ": ")
#define strerr_diewu2sys(e, x1, x2) \
strerr_die6sys(e, PROG, ": warning: ", "unable to ", x1, (x2), ": ")
#define strerr_diewu3sys(e, x1, x2, x3) \
strerr_die7sys(e, PROG, ": warning: ", "unable to ", x1, x2, (x3), ": ")
#define strerr_diewu4sys(e, x1, x2, x3, x4) \
strerr_die8sys(e, PROG, ": warning: ", "unable to ", x1, x2, x3, (x4), ": ")
#define strerr_diewu5sys(e, x1, x2, x3, x4, x5) \
strerr_die9sys(e, PROG, ": warning: ", "unable to ", x1, x2, x3, x4, (x5), ": ")
#define strerr_diewu6sys(e, x1, x2, x3, x4, x5, x6) \
strerr_die10sys(e, PROG, ": warning: ", "unable to ", x1, x2, x3, x4, x5, (x6), ": ")

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

#define strerr_warni1sys(x1) \
strerr_warn4sys(PROG, ": info: ", (x1), ": ")
#define strerr_warni2sys(x1, x2) \
strerr_warn5sys(PROG, ": info: ", (x1), (x2), ": ")
#define strerr_warni3sys(x1, x2, x3) \
strerr_warn6sys(PROG, ": info: ", (x1), x2, (x3), ": ")
#define strerr_warni4sys(x1, x2, x3, x4) \
strerr_warn7sys(PROG, ": info: ", (x1), x2, x3, (x4), ": ")
#define strerr_warni5sys(x1, x2, x3, x4, x5) \
strerr_warn8sys(PROG, ": info: ", (x1), x2, x3, x4, (x5), ": ")
#define strerr_warni6sys(x1, x2, x3, x4, x5, x6) \
strerr_warn9sys(PROG, ": info: ", (x1), x2, x3, x4, x5, (x6), ": ")
#define strerr_warni7sys(x1, x2, x3, x4, x5, x6, x7) \
strerr_warn10sys(PROG, ": info: ", (x1), x2, x3, x4, x5, x6, (x7), ": ")

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

#define strerr_warnt1sys(x1) \
strerr_warn4sys(PROG, ": tracing: ", (x1), ": ")
#define strerr_warnt2sys(x1, x2) \
strerr_warn5sys(PROG, ": tracing: ", (x1), (x2), ": ")
#define strerr_warnt3sys(x1, x2, x3) \
strerr_warn6sys(PROG, ": tracing: ", (x1), x2, (x3), ": ")
#define strerr_warnt4sys(x1, x2, x3, x4) \
strerr_warn7sys(PROG, ": tracing: ", (x1), x2, x3, (x4), ": ")
#define strerr_warnt5sys(x1, x2, x3, x4, x5) \
strerr_warn8sys(PROG, ": tracing: ", (x1), x2, x3, x4, (x5), ": ")
#define strerr_warnt6sys(x1, x2, x3, x4, x5, x6) \
strerr_warn9sys(PROG, ": tracing: ", (x1), x2, x3, x4, x5, (x6), ": ")
#define strerr_warnt7sys(x1, x2, x3, x4, x5, x6, x7) \
strerr_warn10sys(PROG, ": tracing: ", (x1), x2, x3, x4, x5, x6, (x7), ": ")

#endif
