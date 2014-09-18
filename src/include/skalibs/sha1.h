/* ISC license. */

#ifndef SHA1_H
#define SHA1_H

#include <skalibs/uint32.h>

typedef struct SHA1Schedule SHA1Schedule, *SHA1Schedule_ref ;
struct SHA1Schedule
{
  uint32 buf[5] ;
  uint32 bits[2] ;
  uint32 in[16] ;
  unsigned int b ;
} ;

#define SHA1_INIT() { .buf = { 0x67452301UL, 0xefcdab89UL, 0x98badcfeUL, 0x10325476UL, 0xc3d2e1f0UL }, .bits = { 0, 0 }, .in = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, .b = 0 }
extern void sha1_init (SHA1Schedule_ref) ;
extern void sha1_update (SHA1Schedule_ref, char const *, unsigned int) ;
extern void sha1_final (SHA1Schedule_ref, char * /* 20 chars */) ;

#endif
