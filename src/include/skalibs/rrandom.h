/* ISC license. */

#ifndef RRANDOM_H
#define RRANDOM_H

#include <skalibs/unirandom.h>

typedef struct rrandominfo rrandominfo, *rrandominfo_ref, **rrandominfo_ref_ref ;
struct rrandominfo
{
  unirandom it ;
  unsigned int ok ;
} ;

#define RRANDOMINFO_ZERO { .it = UNIRANDOM_ZERO, .ok = 3 }

typedef struct rrandom rrandom, *rrandom_ref, **rrandom_ref_ref ;
struct rrandom
{
  rrandominfo tries[3] ;
  unsigned int n ;
} ;

#define RRANDOM_ZERO { .tries = { RRANDOMINFO_ZERO, RRANDOMINFO_ZERO, RRANDOMINFO_ZERO }, .n = 0 }

extern int rrandom_add (rrandom_ref, int (*) (unirandom_ref)) ;
extern int rrandom_finish (rrandom_ref) ;

extern unsigned int rrandom_read (rrandom_ref, char *, unsigned int, unsigned int (*) (unirandom_ref, char *, unsigned int)) ;
extern unsigned int rrandom_readint (rrandom_ref, unsigned int, unsigned int (*) (unirandom_ref, char *, unsigned int)) ;
#define rrandom_readb(z, s, n) rrandom_read((z), (s), (n), &unirandom_readb)
#define rrandom_readnb(z, s, n) rrandom_read((z), (s), (n), &unirandom_readnb)

extern unsigned int rrandom_name (rrandom_ref, char *, unsigned int, int) ;

#endif
