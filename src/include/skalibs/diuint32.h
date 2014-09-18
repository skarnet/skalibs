/* ISC license. */

#ifndef DIUINT32_H
#define DIUINT32_H

#include <skalibs/uint32.h>

typedef struct diuint32 diuint32, *diuint32_ref ;
struct diuint32
{
  uint32 left ;
  uint32 right ;
} ;

#define DIUINT32_ZERO { .left = 0, .right = 0 }

#endif
