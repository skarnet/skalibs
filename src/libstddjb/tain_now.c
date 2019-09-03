/* ISC license. */

/* MT-unsafe */

#include <skalibs/tai.h>

tain_clockread_func_t_ref tain_now = &tain_wallclock_read ;
