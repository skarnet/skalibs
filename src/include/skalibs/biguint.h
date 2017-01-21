/* ISC license. */

#ifndef BIGUINT_H
#define BIGUINT_H

#include <sys/types.h>
#include <stdint.h>
#include <skalibs/gccattributes.h>

extern void bu_pack (char *, uint32_t const *, unsigned int) ;
extern void bu_unpack (char const *, uint32_t *, unsigned int) ;
extern void bu_pack_big (char *, uint32_t const *, unsigned int) ;
extern void bu_unpack_big (char const *, uint32_t *, unsigned int) ;
extern size_t bu_fmt (char *, uint32_t const *, unsigned int) ;
extern size_t bu_scanlen (char const *, size_t *) ;
extern int bu_scan (char const *, size_t, uint32_t *, unsigned int, size_t) ;

extern unsigned int bu_len (uint32_t const *, unsigned int) gccattr_pure ;
extern void bu_zero (uint32_t *, unsigned int) ;
extern int bu_copy (uint32_t *, unsigned int, uint32_t const *, unsigned int) ;
extern int bu_cmp (uint32_t const *, unsigned int, uint32_t const *, unsigned int) gccattr_pure ;

#define bu_add(c, cn, a, an, b, bn) bu_addc(c, cn, a, an, b, (bn), 0)
extern int bu_addc (uint32_t *, unsigned int, uint32_t const *, unsigned int, uint32_t const *, unsigned int, int) ;
#define bu_sub(c, cn, a, an, b, bn) bu_subc(c, cn, a, an, b, (bn), 0)
extern int bu_subc (uint32_t *, unsigned int, uint32_t const *, unsigned int, uint32_t const *, unsigned int, int) ;
extern int bu_mul (uint32_t *, unsigned int, uint32_t const *, unsigned int, uint32_t const *, unsigned int) ;
extern int bu_div (uint32_t const *, unsigned int, uint32_t const *, unsigned int, uint32_t *, unsigned int, uint32_t *, unsigned int) ;
extern int bu_mod (uint32_t *, unsigned int, uint32_t const *, unsigned int) ;
extern int bu_gcd (uint32_t *, unsigned int, uint32_t const *, unsigned int, uint32_t const *, unsigned int) ;

#define bu_slb(a, n) bu_slbc(a, n, 0)
extern int bu_slbc (uint32_t *, unsigned int, int) ;
#define bu_srb(a, n) bu_srbc(a, n, 0)
extern int bu_srbc (uint32_t *, unsigned int, int) ;

extern int bu_addmod (uint32_t *, unsigned int, uint32_t const *, unsigned int, uint32_t const *, unsigned int, uint32_t const *, unsigned int) ;
extern int bu_submod (uint32_t *, unsigned int, uint32_t const *, unsigned int, uint32_t const *, unsigned int, uint32_t const *, unsigned int) ;
extern int bu_invmod (uint32_t *, unsigned int, uint32_t const *, unsigned int) ;
extern int bu_divmod (uint32_t *, unsigned int, uint32_t const *, unsigned int, uint32_t const *, unsigned int, uint32_t const *, unsigned int) ;

extern void bu_scan_internal (char const *, size_t, uint32_t *) ;
extern void bu_copy_internal (uint32_t *, uint32_t const *, unsigned int) ;
extern void bu_div_internal (uint32_t *, unsigned int, uint32_t const *, unsigned int, uint32_t *, unsigned int) ;
extern void bu_divmod_internal (uint32_t *, uint32_t *, uint32_t const *, unsigned int) ;

#endif
