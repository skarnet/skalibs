/* ISC license. */

#ifndef SKALIBS_SASSSERVER_H
#define SKALIBS_SASSSERVER_H

#include <sys/uio.h>
#include <stdint.h>

#include <skalibs/tai.h>
#include <skalibs/iopause.h>

typedef void *sassserver_send_func (uint32_t, uint32_t, char const *, size_t) ;
typedef sassserver_send_func *sassserver_send_func_ref ;

typedef void sassserver_cancel_func (void *) ;
typedef sassserver_cancel_func *sassserver_cancel_func_ref ;

extern void sassserver_init (char const *, char const *, sassserver_send_func_ref, sassserver_cancel_func_ref, tain const *, tain *stamp) ;
#define sassserver_init_g(banner1, banner2, deadline) sassserver_init(banner1, banner2, (deadline), &STAMP)
extern unsigned int sassserver_prepare_iopause (iopause_fd *, tain *) ;
extern void sassserver_timeout (void) ;
extern int sassserver_event (iopause_fd const *) ;
extern void *sassserver_data (uint32_t) ;

extern void sassserver_async_failure (uint32_t, int) ;
extern void sassserver_async_success (uint32_t, char const *, size_t) ;
extern void sassserver_async_successv (uint32_t, struct iovec const *, unsigned int) ;

#endif
