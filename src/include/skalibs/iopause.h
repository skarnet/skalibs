/* ISC license. */

#ifndef IOPAUSE_H
#define IOPAUSE_H

#include <poll.h>
#include <skalibs/tai.h>

typedef struct pollfd iopause_fd, *iopause_fd_ref ;

#define IOPAUSE_READ (POLLIN|POLLHUP)
#define IOPAUSE_WRITE POLLOUT
#define IOPAUSE_EXCEPT (POLLERR|POLLHUP|POLLNVAL)

typedef int iopause_func_t (iopause_fd *, unsigned int, tain_t const *, tain_t const *) ;
typedef iopause_func_t *iopause_func_t_ref ;

extern iopause_func_t iopause_select ;
extern iopause_func_t iopause_poll ;
extern iopause_func_t iopause_ppoll ;

extern iopause_func_t_ref const iopause_ ;
#define iopause (*iopause_)

extern int iopause_stamp (iopause_fd *, unsigned int, tain_t const *, tain_t *) ;
#define iopause_g(x, n, deadline) iopause_stamp(x, n, (deadline), &STAMP)

extern void deepsleepuntil (tain_t const *, tain_t *) ;
#define deepsleepuntil_g(deadline) deepsleepuntil((deadline), &STAMP)

#endif
