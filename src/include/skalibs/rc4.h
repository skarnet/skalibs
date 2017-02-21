/* ISC license. */

#ifndef RC4_H
#define RC4_H

#include <sys/types.h>

#define RC4_THROWAWAY 128

typedef struct RC4Schedule RC4Schedule, *RC4Schedule_ref ;

struct RC4Schedule
{
  unsigned char tab[256] ;
  unsigned char x, y ;
} ;

extern void rc4_init (RC4Schedule *, char const *, size_t) ;
extern void rc4 (RC4Schedule *, char const *, char *, size_t) ;

#endif
