/* ISC license. */

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

static int fd_read (int fd, char *buf, unsigned int len)
{
  register int r ;
  do r = read(fd, buf, len) ;
  while ((r == -1) && (errno == EINTR)) ;
  return r ;
}

static unsigned int allread (int fd, register char *buf, register unsigned int len)
{
  register unsigned int written = 0 ;
  while (len)
  {
    register int w = fd_read(fd, buf, len) ;
    if (!w) errno = EPIPE ;
    if (w <= 0) break ;
    written += w ;
    buf += w ;
    len -= w ;
  }
  return written ;
}

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
  int fd = open("/dev/random", O_RDONLY) ;
  if ((fd == -1) || (allread(fd, a, 64) < 64) ) return 111 ;
  close(fd) ;
  fd = open("/dev/random", O_RDONLY) ;
  if ((fd == -1) || (allread(fd, b, 64) < 64) ) return 111 ;
  close(fd) ;
  return !byte_diff(a, 64, b) ;
}
