/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

#ifndef _NETBSD_SOURCE
#define _NETBSD_SOURCE
#endif

#ifndef __EXTENSIONS__
#define __EXTENSIONS__
#endif

#include <sys/types.h>
#include <unistd.h>
#include <grp.h>

int main (void)
{
  gid_t gid = getegid() ;
  gid_t list[NGROUPS_MAX] ;
  int i = 0 ;
  int r = getgroups(NGROUPS_MAX, list) ;
  if (r < 0) return 111 ;
  for (; i < r ; i++) if (list[i] == gid) return 0 ;
  return 1 ;
}
