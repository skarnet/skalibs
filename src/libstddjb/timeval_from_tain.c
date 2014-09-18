/* ISC license. */

#include <sys/time.h>
#include <skalibs/tai.h>

int timeval_from_tain (struct timeval *tv, tain_t const *a)
{
  struct timeval tmp ;
  if (!timeval_from_tai(&tmp, tain_secp(a))) return 0 ;
  tv->tv_sec = tmp.tv_sec ;
  tv->tv_usec = a->nano / 1000 ;
  return 1 ;
}
