/* ISC license. */

#ifndef CDB_MAKE_H
#define CDB_MAKE_H

#include <stdint.h>
#include <skalibs/diuint32.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/genalloc.h>
#include <skalibs/buffer.h>

typedef struct cdb_make cdb_make, *cdb_make_ref ;
struct cdb_make
{
  genalloc hplist ; /* array of diuint32 */
  uint32_t pos ;
  buffer b ;
  char buf[BUFFER_OUTSIZE] ;
} ;

#define CDB_MAKE_ZERO { .hplist = GENALLOC_ZERO, .pos = 2048, .b = BUFFER_INIT(&fd_writev, -1, 0, 0) }

extern int cdb_make_start (struct cdb_make *, int) ;
extern int cdb_make_add (struct cdb_make *, char const *, unsigned int, char const *, unsigned int) ;
extern int cdb_make_finish (struct cdb_make *) ;

#endif
