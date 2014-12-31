/* ISC license. */

#ifndef _XPG4_2
#define _XPG4_2
#endif

#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>
#include <errno.h>
#include <skalibs/uint.h>
#include <skalibs/diuint.h>
#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/djbunix.h>
#include <skalibs/unixmessage.h>

 /* MacOS X tries hard to be POSIX-compliant... and fails. */
#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

int unixmessage_sender_flush (unixmessage_sender_t *b)
{
  diuint last = { .left = b->data.len, .right = genalloc_len(int, &b->fds) } ;
  diuint *offsets = genalloc_s(diuint, &b->offsets) ;
  unsigned int n = genalloc_len(diuint, &b->offsets) ;
  unsigned int oldhead = b->head ;
  for (; b->head < n ; b->head++)
  {
    diuint *next = b->head+1 < n ? offsets + b->head+1 : &last ;
    unsigned int len = next->left - offsets[b->head].left ;
    unsigned int nfds = next->right - offsets[b->head].right ;
    char pack[sizeof(unsigned int) << 1] ;
    struct iovec v[2] =
    {
      { .iov_base = pack, .iov_len = sizeof(unsigned int) << 1 },
      { .iov_base = b->data.s + offsets[b->head].left, .iov_len = len }
    } ;
    char ancilbuf[CMSG_SPACE(nfds * sizeof(int))] ;
    struct msghdr hdr =
    {
      .msg_name = 0,
      .msg_namelen = 0,
      .msg_iov = v,
      .msg_iovlen = 2,
      .msg_control = nfds ? ancilbuf : 0,
      .msg_controllen = nfds ? sizeof(ancilbuf) : 0
    } ;
    uint_pack_big(pack, len) ;
    uint_pack_big(pack + sizeof(unsigned int), nfds) ;
    if (nfds)
    {
      struct cmsghdr *cp = CMSG_FIRSTHDR(&hdr) ;
      register unsigned int i = 0 ;
      cp->cmsg_level = SOL_SOCKET ;
      cp->cmsg_type = SCM_RIGHTS ;
      cp->cmsg_len = CMSG_LEN(nfds * sizeof(int)) ;
      for (; i < nfds ; i++)
      {
        register int fd = genalloc_s(int, &b->fds)[offsets[b->head].right + i] ;
        ((int *)CMSG_DATA(cp))[i] = fd < 0 ? -(fd+1) : fd ;
      }
    }
    for (;;)
    {
      register int r = sendmsg(b->fd, &hdr, MSG_NOSIGNAL) ;
      if (r == -1 && errno == EINTR) continue ;
      if (r < (int)(len + (sizeof(unsigned int) << 1)))
        return -(int)(b->head-oldhead)-1 ;
      break ;
    }
#ifndef SKALIBS_HASANCILAUTOCLOSE
    if (nfds)
    {
      register unsigned int i = 0 ;
      for (; i < nfds ; i++)
      {
        register int fd = genalloc_s(int, &b->fds)[offsets[b->head].right + i] ;
        if (fd < 0) fd_close(-(fd+1)) ;
      }
    }
#endif
  }
  b->data.len = 0 ;
  genalloc_setlen(int, &b->fds, 0) ;
  genalloc_setlen(diuint, &b->offsets, 0) ;
  b->head = 0 ;
  return (int)(n - oldhead) ;
}
