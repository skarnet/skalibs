/* ISC license. */

/* MT-unsafe */

#include <stdarg.h>
#include <unistd.h>

#include <skalibs/strerr.h>

void strerr_diel (int e, unsigned int n, ...)
{
  if (n)
  {
    va_list ap ;
    char const *v[n] ;
    va_start(ap, n) ;
    va_arg(ap, unsigned int) ;
    for (unsigned int i = 0 ; i < n ; i++)
      v[i++] = va_arg(ap, char const *) ; 
    va_end(ap) ;
    strerr_warnv(v, n) ;
  }
  _exit(e) ;
}
