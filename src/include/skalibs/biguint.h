/* ISC license. */

#ifndef BIGUINT_H
#define BIGUINT_H

#include <skalibs/gccattributes.h>
#include <skalibs/uint32.h>

extern void bu_pack (char *, uint32 const *, unsigned int) ;
extern void bu_unpack (char const *, uint32 *, unsigned int) ;
extern void bu_pack_big (char *, uint32 const *, unsigned int) ;
extern void bu_unpack_big (char const *, uint32 *, unsigned int) ;
extern unsigned int bu_fmt (char *, uint32 const *, unsigned int) ;
extern unsigned int bu_scanlen (char const *, unsigned int *) ;
extern int bu_scan (char const *, unsigned int, uint32 *, unsigned int, unsigned int) ;

extern unsigned int bu_len (uint32 const *, unsigned int) gccattr_pure ;
extern void bu_zero (uint32 *, unsigned int) ;
extern int bu_copy (uint32 *, unsigned int, uint32 const *, unsigned int) ;
extern int bu_cmp (uint32 const *, unsigned int, uint32 const *, unsigned int) gccattr_pure ;

#define bu_add(c, cn, a, an, b, bn) bu_addc(c, cn, a, an, b, (bn), 0)
extern int bu_addc (uint32 *, unsigned int, uint32 const *, unsigned int, uint32 const *, unsigned int, int) ;
#define bu_sub(c, cn, a, an, b, bn) bu_subc(c, cn, a, an, b, (bn), 0)
extern int bu_subc (uint32 *, unsigned int, uint32 const *, unsigned int, uint32 const *, unsigned int, int) ;
extern int bu_mul (uint32 *, unsigned int, uint32 const *, unsigned int, uint32 const *, unsigned int) ;
extern int bu_div (uint32 const *, unsigned int, uint32 const *, unsigned int, uint32 *, unsigned int, uint32 *, unsigned int) ;
extern int bu_mod (uint32 *, unsigned int, uint32 const *, unsigned int) ;
extern int bu_gcd (uint32 *, unsigned int, uint32 const *, unsigned int, uint32 const *, unsigned int) ;

#define bu_slb(a, n) bu_slbc(a, n, 0)
extern int bu_slbc (uint32 *, unsigned int, int) ;
#define bu_srb(a, n) bu_srbc(a, n, 0)
extern int bu_srbc (uint32 *, unsigned int, int) ;

extern int bu_addmod (uint32 *, unsigned int, uint32 const *, unsigned int, uint32 const *, unsigned int, uint32 const *, unsigned int) ;
extern int bu_submod (uint32 *, unsigned int, uint32 const *, unsigned int, uint32 const *, unsigned int, uint32 const *, unsigned int) ;
extern int bu_invmod (uint32 *, unsigned int, uint32 const *, unsigned int) ;
extern int bu_divmod (uint32 *, unsigned int, uint32 const *, unsigned int, uint32 const *, unsigned int, uint32 const *, unsigned int) ;

extern void bu_scan_internal (char const *, unsigned int, uint32 *) ;
extern void bu_copy_internal (uint32 *, uint32 const *, unsigned int) ;
extern void bu_div_internal (uint32 *, unsigned int, uint32 const *, unsigned int, uint32 *, unsigned int) ;
extern void bu_divmod_internal (uint32 *, uint32 *, uint32 const *, unsigned int) ;

#endif
