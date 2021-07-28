/* ISC license. */

#ifndef SKALIBS_CDBMAKE_H
#define SKALIBS_CDBMAKE_H

#include <stdint.h>

#include <skalibs/diuint32.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/genalloc.h>
#include <skalibs/buffer.h>

typedef struct cdbmaker_s cdbmaker, *cdbmaker_ref ;
struct cdbmaker_s
{
  genalloc hplist ; /* array of diuint32 */
  uint32_t pos ;
  buffer b ;
  char buf[BUFFER_OUTSIZE] ;
} ;

#define CDBMAKER_ZERO { .hplist = GENALLOC_ZERO, .pos = 2048, .b = BUFFER_INIT(&fd_writev, -1, 0, 0) }

extern int cdbmake_start (cdbmaker *, int) ;
extern int cdbmake_add (cdbmaker *, char const *, unsigned int, char const *, unsigned int) ;
extern int cdbmake_finish (cdbmaker *) ;

#endif
