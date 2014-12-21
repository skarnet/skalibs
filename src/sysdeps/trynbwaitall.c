/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#ifndef _XPG4_2
#define _XPG4_2
#endif

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/uio.h>

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT 0
#endif


static int ndelay_on (int fd)
{
  register int got = fcntl(fd, F_GETFL) ;
  return (got == -1) ? -1 : fcntl(fd, F_SETFL, got | O_NONBLOCK) ;
}

static int child (int p, int fd)
{
  char buf[8] ;
  struct iovec v = { .iov_base = buf, .iov_len = 8 } ;
  struct msghdr msg =
  {
    .msg_name = 0,
    .msg_namelen = 0,
    .msg_iov = &v,
    .msg_iovlen = 1,
    .msg_control = 0,
    .msg_controllen = 0
  } ;
  fd_set rfds ;
  if (ndelay_on(fd) < 0) return 111 ;
  FD_ZERO(&rfds) ;
  FD_SET(fd, &rfds) ;
  if (write(p, "", 1) < 1) return 111 ; /* sync with the parent */
  if (select(fd+1, &rfds, 0, 0, 0) < 1) return 111 ;

  /* The following recvmsg may block, despite setting the fd
     non-blocking. That is what we're testing. */

  if (recvmsg(fd, &msg, MSG_WAITALL | MSG_DONTWAIT) < 1) return 111 ;
  if (write(p, "", 1) < 1) return 111 ;
  return 0 ;
}

static int parent (pid_t pid, int p, int fd)
{
  char c ;
  struct iovec v = { .iov_base = &c, .iov_len = 1 } ;
  struct msghdr msg =
  {
    .msg_name = 0,
    .msg_namelen = 0,
    .msg_iov = &v,
    .msg_iovlen = 1,
    .msg_control = 0,
    .msg_controllen = 0
  } ;
  struct timeval tv = { .tv_sec = 2, .tv_usec = 0 } ;
  fd_set rfds ;
  unsigned int n = p > fd ? p : fd ;
  int r ;
  FD_ZERO(&rfds) ;
  FD_SET(p, &rfds) ;
  if (read(p, &c, 1) < 1) return 111 ;
  if (sendmsg(fd, &msg, MSG_NOSIGNAL) < 1) return 111 ;
  for (;;)
  {
    r = select(n+1, &rfds, 0, 0, &tv) ;
    if (r >= 0 || errno != EINTR) break ;
  }
  if (!r) /* child is still blocking on recvmsg() after 2 seconds */
  {
    kill(pid, SIGTERM) ;
    return 1 ;
  }
  if (read(p, &c, 1) < 1) return 111 ;
  return 0 ;
}

int main (void)
{
  pid_t pid ;
  int fd[2] ;
  int p[2] ;
  if (pipe(p) < 0) return 111 ;
  if (socketpair(AF_UNIX, SOCK_STREAM, 0, fd) < 0) return 111 ;
  pid = fork() ;
  if (pid < 0) return 111 ;
  if (!pid)
  {
    close(p[0]) ;
    close(fd[0]) ;
    return child(p[1], fd[1]) ;
  }
  close(p[1]) ;
  close(fd[1]) ;
  return parent(pid, p[0], fd[0]) ;
}
