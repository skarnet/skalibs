/* ISC license. */

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

static int byte_diff (char *s, unsigned int n, char *t)
{
  for (;;)
  {
    if (!n) return 0 ;
    if (*s != *t) break ;
    ++s ; ++t ; --n ;
  }
  return ((int)(unsigned int)(unsigned char) *s)
       - ((int)(unsigned int)(unsigned char) *t);
}

int main ()
{
  char a[64] ;
  char b[64] ;
  int fd ;
  fd = open("/dev/urandom", O_RDONLY) ;
  if ((fd == -1) || (read(fd, a, 64) < 64) ) return 111 ;
  close(fd) ;
  fd = open("/dev/urandom", O_RDONLY) ;
  if ((fd == -1) || (read(fd, b, 64) < 64) ) return 111 ;
  close(fd) ;
  return (!byte_diff(a, 64, b)) ;  
}
