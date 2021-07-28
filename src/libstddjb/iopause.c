/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/iopause.h>

#ifdef SKALIBS_HASPPOLL

iopause_func_ref const iopause_ = &iopause_ppoll ;

#else

#include <skalibs/config.h>

#ifdef SKALIBS_FLAG_PREFERSELECT

iopause_func_ref const iopause_ = &iopause_select ;

#else

iopause_func_ref const iopause_ = &iopause_poll ;

#endif

#endif
