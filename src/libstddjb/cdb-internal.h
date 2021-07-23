/* ISC license. */

#ifndef SKALIBS_CDB_INTERNAL_H
#define SKALIBS_CDB_INTERNAL_H

#include <stdint.h>

#include <skalibs/gccattributes.h>
#include <skalibs/cdb.h>

extern uint32_t cdb_hash (char const *, uint32_t) gccattr_pure ;
extern char const *cdb_p (cdb const *, uint32_t, uint32_t) gccattr_pure ;

#endif
