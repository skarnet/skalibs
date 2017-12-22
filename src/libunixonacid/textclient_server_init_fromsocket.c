/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>
#include <sys/uio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <skalibs/types.h>
#include <skalibs/error.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/djbunix.h>
#include <skalibs/unix-timed.h>
#include <skalibs/textmessage.h>
#include <skalibs/textclient.h>

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

union aligner_u
{
  struct cmsghdr cmsghdr ;
  int i ;
} ;

static int getfd (void *p)
{
  return ((int *)p)[0] ;
}

static int one (void *p)
{
  (void)p ;
  return 1 ;
}

static int sendit (void *p)
{
  int *fd = p ;
  union aligner_u ancilbuf[1 + (CMSG_SPACE(sizeof(int)) - 1) / sizeof(union aligner_u)] ;
  ssize_t r ;
  char ch = '|' ;
  struct iovec v = { .iov_base = &ch, .iov_len = 1 } ;
  struct msghdr hdr =
  {
    .msg_name = 0,
    .msg_namelen = 0,
    .msg_iov = &v,
    .msg_iovlen = 1,
    .msg_control = ancilbuf,
    .msg_controllen = CMSG_SPACE(sizeof(int))
  } ;
  struct cmsghdr *c = CMSG_FIRSTHDR(&hdr) ;
  memset(hdr.msg_control, 0, hdr.msg_controllen) ;
  c->cmsg_level = SOL_SOCKET ;
  c->cmsg_type = SCM_RIGHTS ;
  c->cmsg_len = CMSG_LEN(sizeof(int)) ;
  *(int *)CMSG_DATA(c) = fd[1] ;
  do r = sendmsg(fd[0], &hdr, MSG_NOSIGNAL) ;
  while (r < 0 && errno == EINTR) ;
  if (r <= 0) return 0 ;
#ifndef SKALIBS_HASANCILAUTOCLOSE
  fd_close(fd[1]) ;
#endif
  return 1 ;
}

int textclient_server_init_fromsocket (textmessage_receiver_t *in, textmessage_sender_t *syncout, textmessage_sender_t *asyncout, char const *before, size_t beforelen, char const *after, size_t afterlen, tain_t const *deadline, tain_t *stamp)
{
  int fd[3] = { textmessage_sender_fd(syncout) } ;
  struct iovec v ;
  if (sanitize_read(textmessage_timed_receive(in, &v, deadline, stamp)) <= 0) return 0 ;
  if (v.iov_len != beforelen || memcmp(v.iov_base, before, beforelen)) return (errno = EPROTO, 0) ;
  if (pipenbcoe(fd+1) < 0) return 0 ;
  if (!timed_flush(fd, &getfd, &one, &sendit, deadline, stamp)) goto err ;
  if (!textmessage_timed_send(syncout, after, afterlen, deadline, stamp)) goto err ;
  textmessage_sender_init(asyncout, fd[2]) ;
  if (!textmessage_timed_send(asyncout, after, afterlen, deadline, stamp)) goto err ;
  return 1 ;

 err:
  fd_close(fd[2]) ;
  fd_close(fd[1]) ;
  return 0 ;
}
