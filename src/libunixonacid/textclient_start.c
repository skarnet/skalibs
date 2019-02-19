/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>

#include <sys/uio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>

#include <skalibs/posixishard.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/webipc.h>
#include <skalibs/djbunix.h>
#include <skalibs/unix-timed.h>
#include <skalibs/textmessage.h>
#include <skalibs/textclient.h>

union aligner_u
{
  struct cmsghdr cmsghdr ;
  int i ;
} ;

static int getfd (void *p)
{
  return ((int *)p)[0] ;
}

static ssize_t get (void *p)
{
  static int const awesomeflags =
#ifdef SKALIBS_HASMSGDONTWAIT
    MSG_DONTWAIT
#else
    0
#endif
    |
#ifdef SKALIBS_HASCMSGCLOEXEC
    MSG_CMSG_CLOEXEC
#else
    0
#endif
    ;
  struct cmsghdr *c ;
  int *fd = p ;
  ssize_t r ;
  union aligner_u ancilbuf[1 + (CMSG_SPACE(sizeof(int)) - 1) / sizeof(union aligner_u)] ;
  char ch ;
  struct iovec v = { .iov_base = &ch, .iov_len = 1 } ;
  struct msghdr msghdr =
  {
    .msg_name = 0,
    .msg_namelen = 0,
    .msg_iov = &v,
    .msg_iovlen = 1,
    .msg_flags = 0,
    .msg_control = ancilbuf,
    .msg_controllen = CMSG_SPACE(sizeof(int))
  } ;
  do r = recvmsg(fd[0], &msghdr, awesomeflags) ;
  while (r < 0 && errno == EINTR) ;
  if (r <= 0) return sanitize_read(r) ;
  c = CMSG_FIRSTHDR(&msghdr) ;
  if (ch != '|'
   || !c
   || c->cmsg_level != SOL_SOCKET
   || c->cmsg_type != SCM_RIGHTS
   || (size_t)(c->cmsg_len - (CMSG_DATA(c) - (unsigned char *)c)) != sizeof(int)) return (errno = EPROTO, -1) ;
#ifndef SKALIBS_HASCMSGCLOEXEC
  if (coe(*(int *)CMSG_DATA(c)) < 0)
  {
    fd_close(*(int *)CMSG_DATA(c)) ;
    return -1 ;
  }
#endif
  fd[1] = *(int *)CMSG_DATA(c) ;
  return 1 ;
}


int textclient_start (textclient_t *a, char const *path, uint32_t options, char const *before, size_t beforelen, char const *after, size_t afterlen, tain_t const *deadline, tain_t *stamp)
{
  struct iovec v ;
  int fd[2] ;
  ssize_t r ;
  fd[0] = ipc_stream_nbcoe() ;
  if (fd[0] < 0) return 0 ;
  if (!ipc_timed_connect(fd[0], path, deadline, stamp)) goto err ;
  textmessage_sender_init(&a->syncout, fd[0]) ;
  if (!textmessage_timed_send(&a->syncout, before, beforelen, deadline, stamp)) goto ferr ;
  textmessage_receiver_init(&a->syncin, fd[0], a->syncbuf, TEXTCLIENT_BUFSIZE, TEXTMESSAGE_MAXLEN) ;
  r = timed_get(fd, &getfd, &get, deadline, stamp) ;
  if (!r) errno = EPIPE ;
  if (r <= 0) goto aerr ;
  if (sanitize_read(textmessage_timed_receive(&a->syncin, &v, deadline, stamp)) <= 0) goto perr ;
  if (v.iov_len != afterlen || memcmp(v.iov_base, after, afterlen)) { errno = EPROTO ; goto perr ; }
  textmessage_receiver_init(&a->asyncin, fd[1], a->asyncbuf, TEXTCLIENT_BUFSIZE, TEXTMESSAGE_MAXLEN) ;
  if (sanitize_read(textmessage_timed_receive(&a->asyncin, &v, deadline, stamp)) <= 0) goto serr ;
  if (v.iov_len != afterlen || memcmp(v.iov_base, after, afterlen)) goto berr ;
  a->pid = 0 ;
  a->options = options & ~TEXTCLIENT_OPTION_WAITPID ;
  return 1 ;

 berr:
  errno = EPROTO ;
 serr:
  textmessage_receiver_free(&a->asyncin) ;
 perr:
  fd_close(fd[1]) ;
 aerr:
  textmessage_receiver_free(&a->syncin) ;
 ferr:
  textmessage_sender_free(&a->syncout) ;
 err:
  fd_close(fd[0]) ;
  return 0 ;
}
