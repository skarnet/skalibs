/* ISC license. */

#ifndef _NETBSD_SOURCE
#define _NETBSD_SOURCE
#endif
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <unistd.h>

int main (void)
{
  int p[2] ;
  if (pipe2(p, 0) < 0) return 111 ;
  return 0 ;
}
