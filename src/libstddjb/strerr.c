/* ISC license. */

/* MT-unsafe */

#include <unistd.h>
#include <errno.h>
#include <skalibs/buffer.h>
#include <skalibs/strerr.h>

void strerr_warn (char const *x1, char const *x2, char const *x3, char const *x4, char const *x5, char const *x6, char const *x7, char const *x8, char const *x9, char const *x10, char const *se)
{
  int e = errno ;
  if (x1) buffer_puts(buffer_2, x1) ;
  if (x2) buffer_puts(buffer_2, x2) ;
  if (x3) buffer_puts(buffer_2, x3) ;
  if (x4) buffer_puts(buffer_2, x4) ;
  if (x5) buffer_puts(buffer_2, x5) ;
  if (x6) buffer_puts(buffer_2, x6) ;
  if (x7) buffer_puts(buffer_2, x7) ;
  if (x8) buffer_puts(buffer_2, x8) ;
  if (x9) buffer_puts(buffer_2, x9) ;
  if (x10) buffer_puts(buffer_2, x10) ;
  if (se) buffer_puts(buffer_2, se) ;
  buffer_putflush(buffer_2, "\n", 1) ;
  errno = e ;
}

void strerr_die (int e, char const *x1, char const *x2, char const *x3, char const *x4, char const *x5, char const *x6, char const *x7, char const *x8, char const *x9, char const *x10, char const *se)
{
  strerr_warn(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, se) ;
  _exit(e) ;

 /* No, OpenBSD, this noreturn function does NOT return.
    Please learn what _exit() does. */
}
