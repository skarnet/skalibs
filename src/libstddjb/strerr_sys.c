/* ISC license. */

/* MT-unsafe */

#include <unistd.h>
#include <errno.h>
#include <skalibs/error.h>
#include <skalibs/strerr.h>

void strerr_warnsys (char const *x1, char const *x2, char const *x3, char const *x4, char const *x5, char const *x6, char const *x7, char const *x8, char const *x9, char const *x10)
{
  strerr_warn(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, error_str(errno)) ;
}

void strerr_diesys (int e, char const *x1, char const *x2, char const *x3, char const *x4, char const *x5, char const *x6, char const *x7, char const *x8, char const *x9, char const *x10)
{
  strerr_warnsys(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10) ;
  _exit(e) ;

 /* No, OpenBSD, this noreturn function does NOT return.
    Please learn what _exit() does. */
}
