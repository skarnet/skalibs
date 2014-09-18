/* ISC license. */

#ifndef RC4_H
#define RC4_H

#define RC4_THROWAWAY 128

typedef struct RC4Schedule RC4Schedule, *RC4Schedule_ref ;

struct RC4Schedule
{
  unsigned char tab[256] ;
  unsigned char x, y ;
} ;

extern void rc4_init (RC4Schedule_ref, char const *, unsigned int) ;
extern void rc4 (RC4Schedule_ref, char const *, char *, unsigned int) ;

#endif
