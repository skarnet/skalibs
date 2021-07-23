/* ISC license. */

#ifndef SKALIBS_CDB_H
#define SKALIBS_CDB_H

#include <stdint.h>

#include <skalibs/gccattributes.h>

typedef struct cdb_s cdb, *cdb_ref ;
struct cdb_s
{
  char const *map ;
  uint32_t size ;
} ;
#define CDB_ZERO { .map = 0, .size = 0 }
extern cdb const cdb_zero ;

typedef struct cdb_reader_s cdb_reader, *cdb_reader_ref ;
struct cdb_reader_s
{
  uint32_t loop ;
  uint32_t khash ;
  uint32_t kpos ;
  uint32_t hpos ;
  uint32_t hslots ;
} ;
#define CDB_READER_ZERO { .loop = 0, .khash = 0, .kpos = 0, .hpos = 0, .hslots = 0 }
extern cdb_reader const cdb_reader_zero ;

typedef struct cdb_data_s cdb_data, *cdb_data_ref ;
struct cdb_data_s
{
  char const *s ;
  uint32_t len ;
} ;

extern void cdb_free (cdb *) ;
extern int cdb_init (cdb *, char const *) ;

#define cdb_findstart(d) ((d)->loop = 0)
extern int cdb_find (cdb const *, cdb_reader *, cdb_data *, char const *, uint32_t) ;

#define CDB_TRAVERSE_INIT() 2048
#define cdb_traverse_init(pos) (*pos = 2048)
extern int cdb_traverse_next (cdb const *, cdb_data *, cdb_data *, uint32_t *) ;

#endif
