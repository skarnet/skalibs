/* ISC license. */

#ifndef SKAMISC_H
#define SKAMISC_H

#include <skalibs/buffer.h>
#include <skalibs/stralloc.h>

extern stralloc satmp ;

extern int skagetln (buffer *, stralloc *, char) ;
extern int skagetln_nofill (buffer *, stralloc *, char) ;
extern int skagetlnsep (buffer *, stralloc *, char const *, unsigned int) ;
extern int getlnmax (buffer *, char *, unsigned int, unsigned int *, char) ;
extern int getlnmaxsep (buffer *, char *, unsigned int, unsigned int *, char const *, unsigned int) ;

extern int sauniquename (stralloc *) ;

extern int string_quote (stralloc *, char const *, unsigned int) ;
extern int string_quote_nodelim (stralloc *, char const *, unsigned int) ;
extern int string_quote_nodelim_mustquote (stralloc *, char const *, unsigned int, char const *, unsigned int) ;
extern int string_unquote (char *, unsigned int *, char const *, unsigned int, unsigned int *) ;
extern int string_unquote_nodelim (char *, char const *, unsigned int) ;
extern int string_unquote_withdelim (char *, unsigned int *, char const *, unsigned int, unsigned int *, char const *, unsigned int) ;

extern int string_format (stralloc *, char const *, char const *, char const *const *) ;

#define skaoffsetof(n, s, field) do { s sofoftmp ; *(n) = (unsigned char *)&sofoftmp->field - (unsigned char *)&sofoftmp ; } while (0)

#endif
