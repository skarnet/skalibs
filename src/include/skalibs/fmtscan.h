/* ISC license. */

#ifndef FMTSCAN_H
#define FMTSCAN_H

#include <skalibs/gccattributes.h>
#include <skalibs/uint32.h>


 /* fmt */


extern unsigned char fmtscan_asc (unsigned char) gccattr_const ;

extern unsigned int str_fmt (char *, char const *) ;
extern unsigned int strn_fmt (char *, char const *, unsigned int) ;

#define IP4_FMT 20
extern unsigned int ip4_fmt (char *, char const *) ;
extern unsigned int ip4_fmtu32 (char *, uint32) ;

extern unsigned int ucharn_fmt (char *, char const *, unsigned int) ;
extern unsigned int ucharn_fmt_little (char *, char const *, unsigned int) ;

#define IP6_FMT 40
extern unsigned int ip6_fmt (char *, char const *) ;

#define short_fmt(s, u) long_fmt((s), (long)(u))
#define int_fmt(s, u) long_fmt((s), (long)(u))
extern unsigned int long_fmt (char *, long) ;


 /* scan */


extern unsigned char fmtscan_num (unsigned char, unsigned char) gccattr_const ;

extern unsigned int ip4_scan (char const *, char *) ;
extern unsigned int ip4_scanu32 (char const *, uint32 *) ;
extern unsigned int ip4_scanlist_u32 (uint32 *, unsigned int, char const *, unsigned int *) ;
extern unsigned int ip4_scanlist (char *, unsigned int, char const *, unsigned int *) ;
extern unsigned int ip6_scan (char const *, char *) ;
extern unsigned int ip6_scanlist (char *, unsigned int, char const *, unsigned int *) ;

extern unsigned int ucharn_scan (char const *, char *, unsigned int) ;
extern unsigned int ucharn_scan_little (char const *, char *, unsigned int) ;
extern unsigned int ucharn_findlen (char const *) gccattr_pure ;

extern unsigned int short_scan (char const *, short *) ;
extern unsigned int int_scan (char const *, int *) ;
extern unsigned int long_scan (char const *, long *) ;

#endif
