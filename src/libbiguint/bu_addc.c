/* ISC license. */

/* OpenBSD needs that for EOVERFLOW. wtfbsdseriously */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <errno.h>
#include <skalibs/uint32.h>
#include <skalibs/biguint.h>

int bu_addc (uint32 *c, unsigned int cn, uint32 const *a, unsigned int an, uint32 const *b, unsigned int bn, register int carry)
{
  register unsigned int i = 0 ;
  for (; i < cn ; i++)
  {
    register uint32 ai = (i < an) ? a[i] : 0 ;
    register uint32 bi = (i < bn) ? b[i] : 0 ;
    register uint32 ci = ai + bi + carry ;
    carry = (carry || bi) && (ci < ai) ;
    c[i] = ci ;
  }
  return carry ? (errno = EOVERFLOW, 0) : 1 ;
}
