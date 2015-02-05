/* ISC license. */

#ifndef SIOVEC_H
#define SIOVEC_H

#include <sys/types.h>
#include <sys/uio.h>
#include <skalibs/gccattributes.h>

typedef struct siovec_s siovec_t, *siovec_t_ref ;
struct siovec_s
{
  char *s ;
  unsigned int len ;
} ;

extern unsigned int siovec_len (siovec_t const *, unsigned int) gccattr_pure ;
extern unsigned int siovec_gather (siovec_t const *, unsigned int, char *, unsigned int) ;
extern unsigned int siovec_scatter (siovec_t const *, unsigned int, char const *, unsigned int) ;
extern unsigned int siovec_deal (siovec_t const *, unsigned int, siovec_t const *, unsigned int) ;
extern unsigned int siovec_seek (siovec_t *, unsigned int, unsigned int) ;
extern unsigned int siovec_trunc (siovec_t *, unsigned int, unsigned int) ;

extern void siovec_from_iovec (siovec_t *, struct iovec const *, unsigned int) ;
extern void iovec_from_siovec (struct iovec *, siovec_t const *, unsigned int) ;

extern unsigned int siovec_bytechr (siovec_t const *, unsigned int, char) ;
extern unsigned int siovec_bytein (siovec_t const *, unsigned int, char const *, unsigned int) ;

#endif
