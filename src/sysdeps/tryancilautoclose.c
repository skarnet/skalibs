/* ISC license. */

#undef _POSIX_C_SOURCE
#undef _XOPEN_SOURCE

#ifndef _XPG4_2
# define _XPG4_2
#endif

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/uio.h>
#if defined(__FreeBSD__)
# include <sys/param.h>
#endif

typedef struct ancilbuf_s ancilbuf_t, *ancilbuf_t_ref ;
struct ancilbuf_s
{
  struct cmsghdr h ;
  int fd ;
} ;

static int ancil_send_fd (int sock, int fd)
{
  struct msghdr msghdr ;
  struct iovec nothing_ptr ;
  ancilbuf_t buf ;
  struct cmsghdr *cmsg ;
  char nothing = '!' ;
  
  nothing_ptr.iov_base = &nothing ;
  nothing_ptr.iov_len = 1 ;
  msghdr.msg_name = 0 ;
  msghdr.msg_namelen = 0 ;
  msghdr.msg_iov = &nothing_ptr ;
  msghdr.msg_iovlen = 1 ;
  msghdr.msg_flags = 0 ;
  msghdr.msg_control = &buf ;
  msghdr.msg_controllen = sizeof(ancilbuf_t) ;
  cmsg = CMSG_FIRSTHDR(&msghdr) ;
  cmsg->cmsg_len = msghdr.msg_controllen ;
  cmsg->cmsg_level = SOL_SOCKET ;
  cmsg->cmsg_type = SCM_RIGHTS ;
  *((int *)CMSG_DATA(cmsg)) = fd ;
  return (sendmsg(sock, &msghdr, 0) >= 0) ;
}

static int ancil_recv_fd (int sock)
{
  struct msghdr msghdr ;
  struct iovec nothing_ptr ;
  ancilbuf_t buf ;
  struct cmsghdr *cmsg ;
  char nothing ;

  nothing_ptr.iov_base = &nothing ;
  nothing_ptr.iov_len = 1 ;
  msghdr.msg_name = 0 ;
  msghdr.msg_namelen = 0 ;
  msghdr.msg_iov = &nothing_ptr ;
  msghdr.msg_iovlen = 1 ;
  msghdr.msg_flags = 0 ;
  msghdr.msg_control = &buf ;
  msghdr.msg_controllen = sizeof(ancilbuf_t) ;
  cmsg = CMSG_FIRSTHDR(&msghdr) ;
  cmsg->cmsg_len = msghdr.msg_controllen ;
  cmsg->cmsg_level = SOL_SOCKET ;
  cmsg->cmsg_type = SCM_RIGHTS ;
  *((int *)CMSG_DATA(cmsg)) = -1 ;
  if (recvmsg(sock, &msghdr, 0) < 0) return -1 ;
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
