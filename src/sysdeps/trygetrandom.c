/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <sys/types.h>
#include <sys/syscall.h>

static int getrandom (void *buf, size_t buflen, unsigned int flags)
{
  return syscall(SYS_getrandom, buf, buflen, flags) ;
}

int main (void)
{
  char buf[4] ;
  return getrandom(buf, 4, 0) ;
}
