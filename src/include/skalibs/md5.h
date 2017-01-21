/* ISC license. */

#ifndef MD5_H
#define MD5_H

#include <sys/types.h>
#include <stdint.h>

typedef struct MD5Schedule MD5Schedule, *MD5Schedule_ref ;
struct MD5Schedule
{
  uint32_t buf[4] ;
  uint32_t bits[2] ;
  unsigned char in[64] ;
} ;

#define MD5_INIT() { .buf = { 0x67452301U, 0xefcdab89U, 0x98badcfeU, 0x10325476U }, .bits = { 0, 0 }, .in = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0" }
extern void md5_init (MD5Schedule *) ;
extern void md5_update (MD5Schedule *, char const *, size_t) ;
extern void md5_final (MD5Schedule *, char * /* 16 chars */) ;

#endif
