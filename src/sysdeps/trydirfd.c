/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#ifndef _NETBSD_SOURCE
#define _NETBSD_SOURCE
#endif
#ifndef __EXTENSIONS__
#define __EXTENSIONS__
#endif

#include <dirent.h>

int main (void)
{
  DIR *dir = opendir(".") ;
  return dirfd(dir) ;
}
