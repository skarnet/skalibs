/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#ifndef _NETBSD_SOURCE
#define _NETBSD_SOURCE
#endif

#include <string.h>

int main (void)
{
  return !strcasestr("foobar", "bar") ;
}
