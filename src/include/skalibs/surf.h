/* ISC license. */

#ifndef SKALIBS_SURF_H
#define SKALIBS_SURF_H

#include <skalibs/uint32.h>

typedef struct SURFSchedule SURFSchedule, *SURFSchedule_ref, **SURFSchedule_ref_ref ;
struct SURFSchedule
{
  uint32 seed[32] ;
  uint32 in[12] ;
  char out[32] ;
  unsigned int pos ;
} ;

#define SURFSCHEDULE_ZERO { .seed = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, .in = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, .out = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", .pos = 32 }

extern void surf_sinit (SURFSchedule_ref, char const *) ; /* 160 chars */
extern void surf (SURFSchedule_ref, char *, unsigned int) ;


 /* The following functions need libstdcrypto.a */

extern void surf_makeseed (char *) ; /* fills 160 chars */
extern void surf_init (SURFSchedule_ref) ;
extern void surf_autoinit (SURFSchedule_ref, char *, unsigned int) ;

#endif
