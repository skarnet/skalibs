/* ISC license. */

/* MT-unsafe */

#include <unistd.h>
#include <skalibs/djbunix.h>

void pathexec0 (char const *const *argv)
{
  if (!argv[0]) _exit(0) ;
  pathexec(argv) ;
}
