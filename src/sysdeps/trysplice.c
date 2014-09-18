/* ISC license. */

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define N 4096

int main (void)
{
  char buf[N] ;
  int p[2] ;
  int fd ;
  if (pipe(p) < 0) return 111 ;
  fd = open("./src/sysdeps/trysplice.c", O_RDONLY) ;
  if (fd < 0) return 111 ;

  for (;;)
  {
    register int r = splice(fd, 0, p[1], 0, N, 0) ;
    if (r < 0) return 1 ;
    if (!r) break ;
    if (splice(p[0], 0, 1, 0, r, 0) < r) return 2 ;
  }
  return 0 ;
}
