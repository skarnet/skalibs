/* ISC license. */

#ifndef BITARRAY_H
#define BITARRAY_H

#include <skalibs/gccattributes.h>

#define bitarray_div8(n) ((n) ? 1U + (((n) - 1) >> 3) : 0U)

extern void bitarray_clearsetn (unsigned char *, unsigned int, unsigned int, int) ;
#define bitarray_clearn(s, start, len) bitarray_clearsetn(s, start, (len), 0)
#define bitarray_setn(s, start, len)   bitarray_clearsetn(s, start, (len), 1)

#define bitarray_peek(s, n) (((s)[(n)>>3] & (1U<<((n)&7))) ? 1 : 0)
#define bitarray_isset(b, n) bitarray_peek(b, n)
#define bitarray_clear(s, n) ((s)[(n)>>3] &= ~(1U << ((n) & 7)))
#define bitarray_set(s, n) ((s)[(n)>>3] |= 1U << ((n) & 7))
#define bitarray_poke(s, n, h) ((h) ? bitarray_set(s, n) : bitarray_clear(s, n))

extern int bitarray_testandpoke (unsigned char *, unsigned int, int) ;
#define bitarray_testandclear(b, n) bitarray_testandpoke(b, n, 0)
#define bitarray_testandset(b, n)   bitarray_testandpoke(b, n, 1)

extern unsigned int bitarray_firstclear (unsigned char const *, unsigned int) gccattr_pure ;
extern unsigned int bitarray_firstset (unsigned char const *, unsigned int) gccattr_pure ;
#define bitarray_first(s, n, h) ((h) ? bitarray_firstset(s, n) : bitarray_firstclear(s, n))

extern void bitarray_not (unsigned char *, unsigned int, unsigned int) ;
extern void bitarray_and (unsigned char *, unsigned char const *, unsigned char const *, unsigned int) ;
extern void bitarray_or (unsigned char *, unsigned char const *, unsigned char const *, unsigned int) ;
extern void bitarray_xor (unsigned char *, unsigned char const *, unsigned char const *, unsigned int) ;

#endif
