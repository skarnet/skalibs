/* ISC license. */

#include <errno.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/error.h>
#include <skalibs/unirandom.h>
#include <skalibs/rrandom.h>

unsigned int rrandom_read (rrandom_ref z, char *s, unsigned int n, unsigned int (*f) (unirandom_ref, char *, unsigned int))
{
  unsigned int i = 0 ;
  for (; i < 3 ; i++)
  {
    int r ;
    if (!z->tries[i].ok) continue ;
    r = sanitize_read((*f)(&z->tries[i].it, s, n)) ;
    if (r > 0) return r ;
    z->tries[i].ok = error_temp(errno) ? z->tries[i].ok - 1 : 0 ;
  }
  return (errno = ENOENT, 0) ;
}
