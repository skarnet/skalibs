/* ISC license. */

#ifndef CDB_MAKE_H
#define CDB_MAKE_H

#include <skalibs/uint32.h>
#include <skalibs/diuint32.h>
#include <skalibs/genalloc.h>
#include <skalibs/buffer.h>

typedef struct cdb_make cdb_make, *cdb_make_ref ;
struct cdb_make
{
  char buf[BUFFER_OUTSIZE] ;
  genalloc hplist ; /* diuint32 */
  buffer b ;
  uint32 pos ;
  int fd ;
} ;

#define CDB_MAKE_ZERO { .buf = "", .hplist = GENALLOC_ZERO, .b = BUFFER_INIT(&buffer_write, -1, 0, 0), .pos = 2048, .fd = -1 }

extern int cdb_make_start (struct cdb_make *, int) ;
extern int cdb_make_add (struct cdb_make *, char const *, unsigned int, char const *, unsigned int) ;
extern int cdb_make_finish (struct cdb_make *) ;

#endif
