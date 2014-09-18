/* ISC license. */

#ifndef SHA256_INTERNAL_H
#define SHA256_INTERNAL_H

#include <skalibs/uint32.h>
#include <skalibs/sha256.h>

extern void sha256_feed (SHA256Schedule_ref, unsigned char) ;
extern void sha256_transform (uint32 *, uint32 const *) ;

#endif
