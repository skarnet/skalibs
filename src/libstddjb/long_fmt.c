/* ISC license. */

#include <skalibs/ulong.h>

unsigned int long_fmt (char *fmt, long n)
{
  if (n >= 0) return ulong_fmt(fmt, n) ;
  if (fmt) *fmt++ = '-' ;
  return 1 + ulong_fmt(fmt, -n) ;
}
