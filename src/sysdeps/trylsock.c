/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#ifndef _XPG4_2
# define _XPG4_2
#endif

#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif

#include <sys/types.h>

#if defined(__FreeBSD__)
# include <sys/param.h>
#endif

#include <sys/socket.h>

int main (void)
{
  shutdown(0, 0) ;
  return 0 ;
}
