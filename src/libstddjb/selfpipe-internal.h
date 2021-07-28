/* ISC license. */

/* MT-unsafe */

#ifndef SELFPIPE_INTERNAL_H
#define SELFPIPE_INTERNAL_H

#include <signal.h>
#include <skalibs/sysdeps.h>

extern sigset_t selfpipe_caught ;

#ifdef SKALIBS_HASSIGNALFD

extern int selfpipe_fd ;

#else

#include <skalibs/sig.h>

extern int selfpipe[2] ;
#define selfpipe_fd selfpipe[0]

extern sig_func_ref selfpipe_tophalf ;

#endif

#endif
