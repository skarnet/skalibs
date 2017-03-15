/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif

#ifndef _XPG4_2
#define _XPG4_2
#endif

#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/uio.h>

static int ancil_send_fd (int sock, int fd)
{
  char ancilbuf[CMSG_SPACE(sizeof(int))] ;
  char s[8] = "blahblah" ;
  struct iovec v = { .iov_base = s, .iov_len = 8 } ;
  struct msghdr msghdr =
  {
    .msg_name = 0,
    .msg_namelen = 0,
    .msg_iov = &v,
    .msg_iovlen = 1,
    .msg_flags = 0,
    .msg_control = ancilbuf,
    .msg_controllen = sizeof(ancilbuf)
  } ;
  struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msghdr) ;
  cmsg->cmsg_len = CMSG_LEN(sizeof(int)) ;
  cmsg->cmsg_level = SOL_SOCKET ;
  cmsg->cmsg_type = SCM_RIGHTS ;
  *((int *)CMSG_DATA(cmsg)) = fd ;
  if (sendmsg(sock, &msghdr, 0) < 0) return 0 ;
  return 1 ;
}

static int ancil_recv_fd (int sock)
{
  char ancilbuf[CMSG_SPACE(sizeof(int))] ;
  char s[8] ;
  struct iovec v = { .iov_base = s, .iov_len = 8 } ;
  struct msghdr msghdr =
  {
    .msg_name = 0,
    .msg_namelen = 0,
    .msg_iov = &v,
    .msg_iovlen = 1,
    .msg_flags = 0,
    .msg_control = ancilbuf,
    .msg_controllen = sizeof(ancilbuf)
  } ;
  struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msghdr) ;
  cmsg->cmsg_len = msghdr.msg_controllen ;
  cmsg->cmsg_level = SOL_SOCKET ;
  cmsg->cmsg_type = SCM_RIGHTS ;
  *((int *)CMSG_DATA(cmsg)) = -1 ;
  if (recvmsg(sock, &msghdr, 0) != 8) return -1 ;
  if (memcmp(s, "blahblah", 8)) return -1 ;
  return *((int *)CMSG_DATA(cmsg)) ;
}

static int client (int sock)
{
  int p ;
  char c ;
  if (read(sock, &c, 1) < 1) return 111 ;
  if (c != 'b') return 111 ;
  p = ancil_recv_fd(sock) ;
  if (p < 0) return 111 ;
  if (read(sock, &c, 1) < 1) return 111 ;
  if (c != 'a') return 111 ;
  if (read(p, &c, 1) < 1) return 111 ;
  if (c != 'K') return 111 ;
  if (read(p, &c, 1) < 1) return 111 ;
  return c ;
}

static void server (int sock)
{
  int p[2] ;
  char c = 1 ;
  if (pipe(p) < 0) return ;
  if (write(sock, "b", 1) < 1) return ;
  if (!ancil_send_fd(sock, p[0])) return ;
  if (write(sock, "a", 1) < 1) return ;
  if (write(p[1], "K", 1) < 1) return ;
  if ((close(p[0]) < 0) && (errno == EBADF)) c = 0 ;
  write(p[1], &c, 1) ;
}

int main (void)
{
  int fd[2] ;
  if (socketpair(AF_UNIX, SOCK_STREAM, 0, fd) < 0) return 111 ;
  switch (fork())
  {
    case -1 : return 111 ;
    case 0 : close(fd[0]) ; server(fd[1]) ; return 0 ;
    default : close(fd[1]) ; return client(fd[0]) ;
  }
}
