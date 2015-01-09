/* ISC license. */

#ifndef TAI_H
#define TAI_H

#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <skalibs/gccattributes.h>
#include <skalibs/uint32.h>
#include <skalibs/uint64.h>

typedef struct tai_s tai_t, *tai_t_ref ;
struct tai_s
{
  uint64 x ;
} ;


#define TAI_ZERO { .x = 0 }
#define TAI_MAGIC ((uint64)4611686018427387904ULL)
#define TAI_EPOCH { .x = TAI_MAGIC + 10UL }
#define TAI_INFINITE_RELATIVE { .x = ((uint64)1 << 60) }
#define TAI_INFINITE { .x = TAI_MAGIC + ((uint64)1 << 61) }

#define tai_sec(t) ((t)->x)
extern int tai_u64 (tai_t *, uint64) ;
#define tai_unix(t, u) tai_u64(t, (TAI_MAGIC + (u)))
#define tai_uint(t, u) tai_u64(t, (uint64)(u))

extern int tai_now (tai_t *) ;

#define tai_relative_from_time(t, u) ((t)->x = (uint64)(u), 1)
#define tai_from_time(t, u) tai_unix(t, u)
#define tai_from_time_sysclock(t, u) tai_from_sysclock(t, (uint64)(u) + TAI_MAGIC)
extern int time_from_tai_relative (time_t *, tai_t const *) ;
extern int time_from_tai (time_t *, tai_t const *) ;
extern int time_sysclock_from_tai(time_t *, tai_t const *) ;

extern int tai_from_sysclock (tai_t *, uint64) ;
extern int sysclock_from_tai (uint64 *, tai_t const *) ;

#define tai_approx(t) ((double)(tai_sec(t)))

extern int tai_add (tai_t *, tai_t const *, tai_t const *) ;
extern int tai_sub (tai_t *, tai_t const *, tai_t const *) ;
#define tai_less(t,u) (tai_sec(t) < tai_sec(u))

#define TAI_PACK 8
extern void tai_pack (char *, tai_t const *) ;
extern void tai_unpack (char const *, tai_t *) ;
extern void tai_pack_little (char *, tai_t const *) ;
extern void tai_unpack_little (char const *, tai_t *) ;

typedef struct tain_s tain_t, *tain_t_ref ;
struct tain_s
{
  tai_t sec ;
  uint32 nano ; /* 0..999999999U */
} ;

#define TAIN_ZERO { .sec = TAI_ZERO, .nano = 0 }
#define TAIN_EPOCH { .sec = TAI_EPOCH, .nano = 0 }
#define TAIN_INFINITE { .sec = TAI_INFINITE, .nano = 0 }
#define TAIN_INFINITE_RELATIVE { .sec = TAI_INFINITE_RELATIVE, .nano = 0 }
#define TAIN_NANO500 { .sec = TAI_ZERO, .nano = 500 }

extern tain_t STAMP ; /* the global process wallclock */
extern tain_t const tain_zero ;
extern tain_t const tain_infinite_relative ;
extern tain_t const tain_nano500 ;

#define tain_sec(a) ((a)->sec)
#define tain_secp(a) (&(a)->sec)
#define tain_nano(a) ((a)->nano)

extern int tain_relative_from_timeval (tain_t *, struct timeval const *) ;
extern int tain_from_timeval (tain_t *, struct timeval const *) ;
extern int tain_from_timeval_sysclock (tain_t *, struct timeval const *) ;
extern int timeval_from_tain_relative (struct timeval *, tain_t const *) ;
extern int timeval_from_tain (struct timeval *, tain_t const *) ;
extern int timeval_sysclock_from_tain (struct timeval *, tain_t const *) ;

extern int tain_relative_from_timespec (tain_t *, struct timespec const *) ;
extern int tain_from_timespec (tain_t *, struct timespec const *) ;
extern int tain_from_timespec_sysclock (tain_t *, struct timespec const *) ;
extern int timespec_from_tain_relative (struct timespec *, tain_t const *) ;
extern int timespec_from_tain (struct timespec *, tain_t const *) ;
extern int timespec_sysclock_from_tain (struct timespec *, tain_t const *) ;

extern int sysclock_get (tain_t *) ;
extern int tain_sysclock (tain_t *) ;
extern int tain_from_sysclock (tain_t *, tain_t const *) ;
extern int sysclock_from_tain (tain_t *, tain_t const *) ;
#define tain_sysclock_g() tain_sysclock(&STAMP)
extern int tain_clockmon_init (tain_t *) ;
extern int tain_clockmon (tain_t *, tain_t const *) ;
#define tain_clockmon_g(offset) tain_clockmon(&STAMP, (offset))
extern int tain_init (void) ;
extern int tain_now (tain_t *) ;
#define tain_now_g() tain_now(&STAMP)
#define tain_copynow(t) (*(t) = STAMP)

extern int sysclock_set (tain_t const *) ;
extern int tain_setnow (tain_t const *) ;

extern double tain_approx (tain_t const *) gccattr_pure ;
extern double tain_frac (tain_t const *) gccattr_pure ;

extern int tain_from_millisecs (tain_t *, int) ;
extern int tain_to_millisecs (tain_t const *) gccattr_pure ;

extern int tain_add (tain_t *, tain_t const *, tain_t const *) ;
#define tain_add_g(deadline, tto) tain_add(deadline, &STAMP, tto)
extern int tain_addsec (tain_t *, tain_t const *, int) ;
#define tain_addsec_g(deadline, n) tain_addsec(deadline, &STAMP, n)
extern int tain_sub (tain_t *, tain_t const *, tain_t const *) ;
extern int tain_less (tain_t const *, tain_t const *) gccattr_pure ;
#define tain_future(deadline) tain_less(&STAMP, (deadline))

#define TAIN_PACK 12
extern void tain_pack (char *, tain_t const *) ;
extern void tain_unpack (char const *, tain_t *) ;
extern void tain_pack_little (char *, tain_t const *) ;
extern void tain_unpack_little (char const *, tain_t *) ;

#define TAIN_FMT 25
extern unsigned int tain_fmt (char *, tain_t const *) ;
extern unsigned int tain_scan (char const *, tain_t *) ;

#define TAIN_FMTFRAC 19
extern unsigned int tain_fmtfrac (char *, tain_t const *) ;

#define tain_uint(a, u) tain_ulong(a, u)
extern int tain_ulong (tain_t *, unsigned long) ;
extern void tain_half (tain_t *, tain_t const *) ;

#define TIMESTAMP (1 + (TAIN_PACK << 1))
extern unsigned int timestamp_fmt (char *, tain_t const *) ;
extern unsigned int timestamp_scan (char const *, tain_t *) ;
extern int timestamp_r (char *, tain_t *) ;
extern int timestamp (char *) ;
#define timestamp_g(s) timestamp_fmt((s), &STAMP)

#endif
