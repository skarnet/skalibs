/* ISC license. */

#ifndef NETSTRING_H
#define NETSTRING_H

#include <sys/types.h>
#include <sys/uio.h>
#include <string.h>
#include <skalibs/buffer.h>
#include <skalibs/stralloc.h>

extern int netstring_appendb (stralloc *, char const *, size_t) ;
#define netstring_appends(sa, s) netstring_appendb((sa), (s), strlen(s))
#define netstring_append(to, from) netstring_appendb((to), (from)->s, (from)->len)
extern int netstring_appendv (stralloc *, struct iovec const *, unsigned int) ;

extern int netstring_encode (stralloc *, char const *, size_t) ;
extern ssize_t netstring_decode (stralloc *, char const *, size_t) ;

extern int netstring_okeof (buffer *, size_t) ;
extern int netstring_get (buffer *, stralloc *, size_t *) ;
extern int netstring_put (buffer *, char const *, size_t, size_t *) ;
#define netstring_putba(ba, s, n) netstring_appendb(&(ba)->x, s, n)
#define netstring_putbav(ba, v, n) netstring_appendv(&(ba)->x, v, n)

#endif
