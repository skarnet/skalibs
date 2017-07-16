/* ISC license. */

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSPLICE

#include <skalibs/djbunix.h>
#include <skalibs/iobuffer.h>

static void iobufferk_nop (iobufferk *k)
{
  (void)k ;
}

static void iobufferk_finish_0 (iobufferk *k)
{
  fd_close(k->p[1]) ;
}

static void iobufferk_finish_3 (iobufferk *k)
{
  fd_close(k->p[1]) ;
  fd_close(k->p[0]) ;
}

iobufferk_finish_func_t_ref const iobufferk_finish_f[4] =
{
  &iobufferk_finish_0, &iobufferk_nop, &iobufferk_nop, &iobufferk_finish_3
} ;

#else

#include <skalibs/iobuffer.h>

static void iobufferk_nop (iobufferk *k)
{
  (void)k ;
}

iobufferk_finish_func_t_ref const iobufferk_finish_f[4] =
{
  &iobufferk_nop, &iobufferk_nop, &iobufferk_nop, &iobufferk_nop
} ;

#endif
