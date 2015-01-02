/* ISC license. */

#ifndef DJBTIME_H
#define DJBTIME_H

#include <time.h>
#include <skalibs/config.h>
#include <skalibs/uint32.h>
#include <skalibs/uint64.h>
#include <skalibs/tai.h>


/* UTC <--> TAI conversions */
/* sysclock can be either TAI-10 or UTC */

extern int utc_from_tai (uint64 *, tai_t const *) ;
extern int tai_from_utc (tai_t *, uint64) ;
extern int utc_from_sysclock (uint64 *) ;
extern int sysclock_from_utc (uint64 *) ;


/* NTP internal format */

#define NTP_OFFSET 2208988800UL
extern int ntp_from_tain (uint64 *, tain_t const *) ;
extern int tain_from_ntp (tain_t *, uint64) ;


/* localtime handling - replaces caltimedate functions */
/* ltm64 can be either TAI-10 or UTC depending on the current timezone */
/* normally ltm64 is the same as sysclock, but we allow it to be different */
/* for instance for musl TAI-10 systems */

typedef struct localtmn_s localtmn_t, *localtmn_t_ref ;
struct localtmn_s
{
  struct tm tm ;
  uint32 nano ;
} ;

extern int ltm64_from_tai (uint64 *, tai_t const *) ;
extern int tai_from_ltm64 (tai_t *, uint64) ;
extern int ltm64_from_utc (uint64 *) ;
extern int utc_from_ltm64 (uint64 *) ;
extern int ltm64_from_sysclock (uint64 *) ;
extern int sysclock_from_ltm64 (uint64 *) ;

extern int localtm_from_ltm64 (struct tm *, uint64, int) ;
extern int ltm64_from_localtm (uint64 *, struct tm const *) ;
extern int localtm_from_sysclock (struct tm *, uint64, int) ;
extern int sysclock_from_localtm (uint64 *, struct tm const *) ;
extern int localtm_from_utc (struct tm *, uint64, int) ;
extern int utc_from_localtm (uint64 *, struct tm const *) ;
extern int localtm_from_tai (struct tm *, tai_t const *, int) ;
extern int tai_from_localtm (tai_t *, struct tm const *) ;

extern int localtmn_from_tain (localtmn_t *, tain_t const *, int) ;
extern int tain_from_localtmn (tain_t *, localtmn_t const *) ;
extern int localtmn_from_sysclock (localtmn_t *, tain_t const *, int) ;
extern int sysclock_from_localtmn (tain_t *, localtmn_t const *) ;

#define LOCALTM_FMT 21
extern unsigned int localtm_fmt (char *, struct tm const *) ;
extern unsigned int localtm_scan (char const *, struct tm *) ;

#define LOCALTMN_FMT 31
extern unsigned int localtmn_fmt (char *, localtmn_t const *) ;
extern unsigned int localtmn_scan (char const *, localtmn_t *) ;

#endif
