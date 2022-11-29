/* ISC license. */

/* MT-unsafe */

#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <skalibs/strerr.h>

void strerr_dielsys (int e, unsigned int n, ...)
{
  va_list ap ;
  char const *v[n+1] ;
  va_start(ap, n) ;
  va_arg(ap, unsigned int) ;
  for (unsigned int i = 0 ; i < n ; i++)
    v[i++] = va_arg(ap, char const *) ; 
  va_end(ap) ;
  v[n] = strerror(errno) ;
  strerr_diev(e, v, n+1) ;
}
