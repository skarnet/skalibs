/* ISC license. */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <poll.h>

int main (void)
{
  struct pollfd x = { .events = POLLIN } ;
  struct timespec ts = { .tv_sec = 0, .tv_nsec = 10 } ;
  x.fd = open("src/sysdeps/tryppoll.c", O_RDONLY);
  if (x.fd < 0) return 111 ;
  if (ppoll(&x, 1, &ts, 0) < 0) return 1 ;
  if (x.revents != POLLIN) return 1 ;
  return 0 ;
}
