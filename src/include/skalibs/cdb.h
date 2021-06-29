/* ISC license. */

#ifndef CDB_H
#define CDB_H

#include <stdint.h>
#include <skalibs/gccattributes.h>

#define CDB_HASHSTART 5381
extern uint32_t cdb_hashadd (uint32_t, unsigned char) gccattr_const ;
extern uint32_t cdb_hash (char const *, unsigned int) gccattr_pure ;

typedef struct cdb cdb_t, *cdb_t_ref ;
struct cdb
{
  char *map ;
  uint32_t size ; /* initialized if map is nonzero */
  uint32_t loop ; /* number of hash slots searched under this key */
  uint32_t khash ; /* initialized if loop is nonzero */
  uint32_t kpos ; /* initialized if loop is nonzero */
  uint32_t hpos ; /* initialized if loop is nonzero */
  uint32_t hslots ; /* initialized if loop is nonzero */
  uint32_t dpos ; /* initialized if cdb_findnext() returns 1 */
  uint32_t dlen ; /* initialized if cdb_findnext() returns 1 */
} ;

#define CDB_ZERO { .map = 0, .size = 0, .loop = 0, .khash = 0, .kpos = 0, .hpos = 0, .hslots = 0, .dpos = 0, .dlen = 0 }
extern struct cdb const cdb_zero ;

extern void cdb_free (struct cdb *) ;

#define cdb_init_map(c, fd, domap) (!cdb_init(c, fd))
extern int cdb_init (struct cdb *, int fd) ;
extern int cdb_mapfile (struct cdb *, char const *) ;
extern int cdb_read (struct cdb *, char *, unsigned int, uint32_t) ;
#define cdb_findstart(c) ((c)->loop = 0)
extern int cdb_findnext (struct cdb *, char const *, unsigned int) ;
#define cdb_find(c, s, len) (cdb_findstart(c), cdb_findnext(c, s, len))

#define cdb_datapos(c) ((c)->dpos)
#define cdb_datalen(c) ((c)->dlen)
#define cdb_keypos(c) ((c)->kpos)
#define cdb_keylen(c) ((c)->dpos - (c)->kpos)

#define cdb_traverse_init(c, kpos) (*(kpos) = 2048)
#define cdb_firstkey(c, kpos) (cdb_traverse_init(c, kpos), cdb_nextkey(c, kpos))
extern int cdb_nextkey (struct cdb *, uint32_t *) ;
extern int cdb_successor (struct cdb *, char const *, unsigned int) ;

#endif
