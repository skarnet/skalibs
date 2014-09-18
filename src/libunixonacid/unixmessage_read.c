/* ISC license. */

#define _XPG4_2
#include <skalibs/sysdeps.h>
#include <skalibs/nonposix.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <skalibs/buffer.h>
#include <skalibs/cbuffer.h>
#include <skalibs/djbunix.h>
#include <skalibs/error.h>
#include <skalibs/siovec.h>
#include <skalibs/unixmessage.h>

int unixmessage_read (int fd, siovec_t const *v, unsigned int n, void *aux)
{
  int r ;
  char ancilbuf[CMSG_SPACE(UNIXMESSAGE_MAXFDS * sizeof(int))] ;
  struct iovec iov[n] ;
  struct msghdr msghdr =
  {
    .msg_name = 0,
    .msg_namelen = 0,
    .msg_iov = iov,
    .msg_iovlen = n,
    .msg_flags = 0,
    .msg_control = ancilbuf,
    .msg_controllen = sizeof(ancilbuf)
  } ;
  iovec_from_siovec(iov, v, n) ;
#ifdef SKALIBS_HASCMSGCLOEXEC
  r = recvmsg(fd, &msghdr, MSG_WAITALL | MSG_CMSG_CLOEXEC) ;
#else
  r = recvmsg(fd, &msghdr, MSG_WAITALL) ;
#endif
  if (r > 0)
  {
    struct cmsghdr *c = CMSG_FIRSTHDR(&msghdr) ;
    if (c)
    {
      cbuffer_t *auxb = aux ;
      unsigned int len ;
      if (c->cmsg_level != SOL_SOCKET
       || c->cmsg_type != SCM_RIGHTS) return (errno = EPROTO, -1-r) ;
      len = (unsigned int)(c->cmsg_len - (CMSG_DATA(c) - (unsigned char *)c)) ;
#ifndef SKALIBS_HASCMSGCLOEXEC
      {
        register unsigned int i = 0 ;
        for (; i < len/sizeof(int) ; i++)
          if (coe(((int *)CMSG_DATA(c))[i]) < 0) return -1-r ;
      }
#endif
      if (msghdr.msg_flags | MSG_CTRUNC) return (errno = EPROTO, -1-r) ;
      if (cbuffer_put(auxb, (char *)CMSG_DATA(c), len) < len)
        return (errno = ENOBUFS, -1-r) ;
    }
  }
  return r ;
}
