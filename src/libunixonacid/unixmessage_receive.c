/* ISC license. */

#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <skalibs/uint.h>
#include <skalibs/cbuffer.h>
#include <skalibs/djbunix.h>
#include <skalibs/error.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/stralloc.h>
#include <skalibs/siovec.h>
#include <skalibs/unixmessage.h>

static int const awesomeflags =
#ifdef SKALIBS_HASMSGDONTWAIT
  MSG_DONTWAIT
#else
  0
#endif
  |
#ifdef SKALIBS_HASNBWAITALL
  MSG_WAITALL
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

static int unixmessage_receiver_fill (unixmessage_receiver_t *b)
{
  char ancilbuf[CMSG_SPACE(b->auxb.a - 1)] ;
  struct iovec iov[2] ;
  struct msghdr msghdr =
  {
    .msg_name = 0,
    .msg_namelen = 0,
    .msg_iov = iov,
    .msg_iovlen = 2,
    .msg_flags = 0,
    .msg_control = ancilbuf,
    .msg_controllen = sizeof(ancilbuf)
  } ;
  unsigned int auxlen ;
  int r ;
  if (cbuffer_isfull(&b->mainb) || cbuffer_isfull(&b->auxb))
    return (errno = ENOBUFS, -1) ;
  {
    siovec_t v[2] ;
    cbuffer_wpeek(&b->mainb, v) ;
    iovec_from_siovec(iov, v, 2) ;
  }
  r = recvmsg(b->fd, &msghdr, awesomeflags) ;
  if (r <= 0) return r ;
  {
    struct cmsghdr *c = CMSG_FIRSTHDR(&msghdr) ;
    if (c)
    {
      if (c->cmsg_level != SOL_SOCKET
       || c->cmsg_type != SCM_RIGHTS) return (errno = EPROTO, -1) ;
      auxlen = (unsigned int)(c->cmsg_len - (CMSG_DATA(c) - (unsigned char *)c)) ;
#ifndef SKALIBS_HASCMSGCLOEXEC
      {
        register unsigned int i = 0 ;
        for (; i < auxlen/sizeof(int) ; i++)
          if (coe(((int *)CMSG_DATA(c))[i]) < 0) return -1 ;
      }
#endif
      if (msghdr.msg_flags & MSG_CTRUNC) return (errno = EPROTO, -1) ;
      if (cbuffer_put(&b->auxb, (char *)CMSG_DATA(c), auxlen) < auxlen)
        return (errno = ENOBUFS, -1) ;
    }
  }
  cbuffer_WSEEK(&b->mainb, r) ;
  return 1 ;
}

int unixmessage_receive (unixmessage_receiver_t *b, unixmessage_t *m)
{
  if (b->maindata.len == b->mainlen && b->auxdata.len == b->auxlen)
  {
    char pack[sizeof(unsigned int) << 1] ;
    if (cbuffer_len(&b->mainb) < sizeof(unsigned int) << 1)
    {
      register int r = sanitize_read(unixmessage_receiver_fill(b)) ;
      if (r <= 0) return r ;
      if (cbuffer_len(&b->mainb) < sizeof(unsigned int) << 1)
        return (errno = EWOULDBLOCK, 0) ;
    }
    cbuffer_get(&b->mainb, pack, sizeof(unsigned int) << 1) ;
    uint_unpack_big(pack, &b->mainlen) ;
    uint_unpack_big(pack + sizeof(unsigned int), &b->auxlen) ;
    b->auxlen *= sizeof(int) ;
    if (!stralloc_ready(&b->maindata, b->mainlen)) return -1 ;
    b->maindata.len = 0 ;
    if (!stralloc_ready(&b->auxdata, b->auxlen)) return -1 ;
    b->auxdata.len = 0 ;
  }

  for (;;)
  {
    register int r ;
    register unsigned int n = cbuffer_len(&b->mainb) ;
    if (n > b->mainlen - b->maindata.len) n = b->mainlen - b->maindata.len ;
    b->maindata.len += cbuffer_get(&b->mainb, b->maindata.s + b->maindata.len, n) ;
    n = cbuffer_len(&b->auxb) ;
    if (n > b->auxlen - b->auxdata.len) n = b->auxlen - b->auxdata.len ;
    b->auxdata.len += cbuffer_get(&b->auxb, b->auxdata.s + b->auxdata.len, n) ;
    if (b->maindata.len == b->mainlen && b->auxdata.len == b->auxlen) break ;
    r = sanitize_read(unixmessage_receiver_fill(b)) ;
    if (r <= 0) return r ;
  }

  m->s = b->maindata.s ;
  m->len = b->maindata.len ;
  m->fds = (int *)b->auxdata.s ;
  m->nfds = b->auxlen / sizeof(int) ;
  return 1 ;
}
