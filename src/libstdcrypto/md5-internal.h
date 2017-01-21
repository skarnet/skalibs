/* ISC license. */

#ifndef MD5_INTERNAL_H
#define MD5_INTERNAL_H

#include <stdint.h>
#include <skalibs/md5.h>

extern void md5_transform (uint32_t * /* 4 uint32s */, uint32_t const * /* 16 uint32s */) ;

#endif
