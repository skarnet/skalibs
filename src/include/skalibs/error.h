/* ISC license. */

#ifndef ERROR_H
#define ERROR_H

#include <skalibs/sysdeps.h>
#include <skalibs/gccattributes.h>

extern int error_temp (int) gccattr_const ;
#define error_isagain(e) (((e) == EAGAIN) || ((e) == EWOULDBLOCK))

#ifdef SKALIBS_BSD_SUCKS
# define error_isalready(e) (((e) == EALREADY) || ((e) == EINPROGRESS) || ((e) == EADDRINUSE))
#else
# define error_isalready(e) (((e) == EALREADY) || ((e) == EINPROGRESS))
#endif

#endif
