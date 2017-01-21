/* ISC license. */

/* SHA256 routines */
/* Written by David Madore (<URL: http://www.madore.org/~david/ >) */
/* Adapted by Laurent Bercot. */
/* This version last modified 2010-01-08 */

/* Note: these routines do not depend on endianness. */

#ifndef SHA256_H
#define SHA256_H

#include <sys/types.h>
#include <stdint.h>

typedef struct SHA256Schedule_s SHA256Schedule, *SHA256Schedule_ref ;
struct SHA256Schedule_s
{
  uint32_t buf[8] ;   /* The eight chaining variables */
  uint32_t bits[2] ;  /* Count number of message bits */
  uint32_t in[16] ;   /* Data being fed in */
  unsigned int b ;  /* Our position within the 512 bits (always between 0 and 63) */
} ;

#define SHA256_INIT() { .buf = { 0x6a09e667U, 0xbb67ae85U, 0x3c6ef372U, 0xa54ff53aU, 0x510e527fU, 0x9b05688cU, 0x1f83d9abU, 0x5be0cd19U }, .bits = { 0, 0 }, .in = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, .b = 0 }
extern void sha256_init (SHA256Schedule *) ;
extern void sha256_update (SHA256Schedule *, char const *, size_t) ;
extern void sha256_final (SHA256Schedule *, char *digest) ;

#endif
