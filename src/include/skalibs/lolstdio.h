/* ISC license. */

#ifndef SKALIBS_LOLSTDIO_H
#define SKALIBS_LOLSTDIO_H

#include <stdarg.h>

#include <skalibs/buffer.h>
#include <skalibs/bufalloc.h>
#include <skalibs/strerr2.h>

#ifdef DEBUG
# define LOLDEBUG(...) do \
  { \
    buffer_puts(buffer_2, PROG) ; \
    buffer_puts(buffer_2, ": debug: ") ; \
    bprintf(buffer_2, __VA_ARGS__) ; \
    buffer_putflush(buffer_2, "\n", 1) ; \
  } while (0)
#else
# define LOLDEBUG(...)
#endif

extern int vbprintf (buffer *, char const *, va_list) ;
extern int bprintf (buffer *, char const *, ...) ;
extern int lolprintf (char const *, ...) ;

extern int vbaprintf (bufalloc *, char const *, va_list) ;
extern int baprintf (bufalloc *, char const *, ...) ;

#endif
