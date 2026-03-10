/* ISC license. */

#ifndef SKALIBS_SASSSERVER_H
#define SKALIBS_SASSSERVER_H

#include <sys/uio.h>
#include <stdint.h>

#include <skalibs/tai.h>
#include <skalibs/iopause.h>
#include <skalibs/gensetdyn.h>
#include <skalibs/avltree.h>

typedef int sassserver_send_func (void *, uint32_t, uint32_t, uint32_t, char const *, size_t) ;
typedef sassserver_send_func *sassserver_send_func_ref ;

typedef void sassserver_cancel_func (void *) ;
typedef sassserver_cancel_func *sassserver_cancel_func_ref ;

typedef struct sassserver_s sassserver, *sassserver_ref ;
struct sassserver_s
{
  sassserver_send_func_ref sendf ;
  sassserver_cancel_func_ref cancelf ;
  size_t datasize ;
  gensetdyn queries ;
  avltree by_deadline ;
  avltree by_id ;
} ;
#define SASSSERVER_ZERO { .sendf = 0, .cancelf = 0, .datasize = 0, .queries = GENSETDYN_ZERO, .by_deadline = AVLTREE_ZERO, .by_id = AVLTREE_ZERO }

extern void sassserver_init (sassserver *, char const *, char const *, sassserver_send_func_ref, sassserver_cancel_func_ref, size_t, tain const *, tain *stamp) ;
#define sassserver_init_g(a, banner1, banner2, sendf, cancelf, esize, deadline) sassserver_init(a, banner1, banner2, sendf, cancelf, esize, (deadline), &STAMP)
extern unsigned int sassserver_prepare_iopause (sassserver const *, iopause_fd *, tain *) ;
extern void sassserver_timeout (sassserver *) ;
extern int sassserver_event (sassserver *, iopause_fd const *) ;
extern void *sassserver_data (sassserver const *, uint32_t) ;

extern void sassserver_async_failure (sassserver *, uint32_t, int) ;
extern void sassserver_async_success (sassserver *, uint32_t, uint32_t, char const *, size_t) ;
extern void sassserver_async_successv (sassserver *, uint32_t, uint32_t, struct iovec const *, unsigned int) ;

#endif
