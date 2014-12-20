/* ISC license. */

/* SHA256 routines */
/* Written by David Madore (<URL: http://www.madore.org/~david/ >) */
/* Adapted by Laurent Bercot. */
/* This version last modified 2010-01-08 */

/* Note: these routines do not depend on endianness. */

#ifndef SHA256_H
#define SHA256_H

#include <skalibs/uint32.h>

typedef struct SHA256Schedule_s SHA256Schedule, *SHA256Schedule_ref ;
struct SHA256Schedule_s
{
  uint32 buf[8] ;   /* The eight chaining variables */
  uint32 bits[2] ;  /* Count number of message bits */
  uint32 in[16] ;   /* Data being fed in */
  unsigned int b ;  /* Our position within the 512 bits (always between 0 and 63) */
} ;

#define SHA256_INIT() { .buf = { 0x6a09e667UL, 0xbb67ae85UL, 0x3c6ef372UL, 0xa54ff53aUL, 0x510e527fUL, 0x9b05688cUL, 0x1f83d9abUL, 0x5be0cd19UL }, .bits = { 0, 0 }, .in = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, .b = 0 }
extern void sha256_init (SHA256Schedule *) ;
extern void sha256_update (SHA256Schedule *, char const *, unsigned int) ;
extern void sha256_final (SHA256Schedule *, char *digest) ;

#endif
