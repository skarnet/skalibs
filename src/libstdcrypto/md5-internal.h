/* ISC license. */

#ifndef MD5_INTERNAL_H
#define MD5_INTERNAL_H

#include <skalibs/uint32.h>
#include <skalibs/md5.h>

extern void md5_transform (uint32 * /* 4 uint32s */, uint32 const * /* 16 uint32s */) ;

#endif
