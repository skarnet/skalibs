/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#ifndef _NETBSD_SOURCE
#define _NETBSD_SOURCE
#endif
#ifndef _DARWIN_C_SOURCE
#define _DARWIN_C_SOURCE
#endif

#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h>
#include <signal.h>

static void alrm_handler (int sig)
{
  (void)sig ;
  _exit(1) ;
}

int main (void)
{
  struct sigaction action = { .sa_handler = &alrm_handler, .sa_flags = SA_NOCLDSTOP | SA_RESTART } ;
  struct timeval tv = { .tv_sec = 100000000, .tv_usec = 0 } ;
  fd_set r, w, x ;
  FD_ZERO(&r) ;
  FD_ZERO(&w) ;
  FD_ZERO(&x) ;
  sigfillset(&action.sa_mask) ;
  if (sigaction(SIGALRM, &action, 0) == -1) _exit(111) ;
  alarm(1) ;
  if (select(1, &r, &w, &x, &tv) == -1) _exit(errno == EINVAL ? 0 : 111) ;
  _exit(1) ;
}
