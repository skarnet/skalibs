/* ISC license. */

#ifndef SKALIBS_STAT_H
#define SKALIBS_STAT_H

#include <skalibs/sysdeps.h>

#ifdef SKALIBS_HASSTATIM

#define ST_ATIM st_atim
#define ST_MTIM st_mtim
#define ST_CTIM st_ctim

#else

#ifdef SKALIBS_HASSTATIMESPEC

#define ST_ATIM st_atimespec
#define ST_MTIM st_mtimespec
#define ST_CTIM st_ctimespec

#else

#define ST_ATIM st_how_the_fuck_do_you_even_get_atime_on_this_OS
#define ST_MTIM st_how_the_fuck_do_you_even_get_mtime_on_this_OS
#define ST_CTIM st_how_the_fuck_do_you_even_get_ctime_on_this_OS

#endif
#endif

#endif
