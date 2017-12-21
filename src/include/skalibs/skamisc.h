/* ISC license. */

#ifndef SKAMISC_H
#define SKAMISC_H

#include <sys/types.h>
#include <skalibs/buffer.h>
#include <skalibs/stralloc.h>

extern stralloc satmp ;

extern int skagetln (buffer *, stralloc *, char) ;
extern int skagetln_nofill (buffer *, stralloc *, char) ;
extern int skagetlnsep (buffer *, stralloc *, char const *, size_t) ;
extern int skagetlnmaxsep (buffer *, stralloc *, size_t, char const *, size_t) ;
extern int getlnmax (buffer *, char *, size_t, size_t *, char) ;
extern int getlnmaxsep (buffer *, char *, size_t, size_t *, char const *, size_t) ;

extern int sauniquename (stralloc *) ;

extern int string_quote (stralloc *, char const *, size_t) ;
extern int string_quote_nodelim (stralloc *, char const *, size_t) ;
extern int string_quote_nodelim_mustquote (stralloc *, char const *, size_t, char const *, size_t) ;
extern int string_unquote (char *, size_t *, char const *, size_t, size_t *) ;
extern ssize_t string_unquote_nodelim (char *, char const *, size_t) ;
extern int string_unquote_withdelim (char *, size_t *, char const *, size_t, size_t *, char const *, size_t) ;

extern int string_format (stralloc *, char const *, char const *, char const *const *) ;

#define skaoffsetof(n, s, field) do { s sofoftmp ; *(n) = (unsigned char *)&sofoftmp->field - (unsigned char *)&sofoftmp ; } while (0)

#endif
