/* ISC license. */

#include <sys/uio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#include <skalibs/posixishard.h>
#include <skalibs/types.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/djbunix.h>
#include <skalibs/textmessage.h>
#include <skalibs/textclient.h>

int textclient_server_init_frompipe (textmessage_receiver_t *in, textmessage_sender_t *syncout, textmessage_sender_t *asyncout, char const *before, size_t beforelen, char const *after, size_t afterlen, tain_t const *deadline, tain_t *stamp)
{
  struct iovec v ;
  unsigned int asyncfd ;
  char *x = getenv(SKALIBS_CHILD_SPAWN_FDS_ENVVAR) ;
  if (!x
   || !uint0_scan(x, &asyncfd)
   || asyncfd == textmessage_sender_fd(syncout)
   || asyncfd == textmessage_receiver_fd(in)) return (errno = EPROTO, 0) ;
  if (sanitize_read(textmessage_timed_receive(in, &v, deadline, stamp)) <= 0) return 0 ;
  if (v.iov_len != beforelen || memcmp(v.iov_base, before, beforelen)) return (errno = EPROTO, 0) ;
  if (fcntl(asyncfd, F_GETFD) < 0) return 0 ;
  if (!textmessage_timed_send(syncout, after, afterlen, deadline, stamp)) return 0 ;
  textmessage_sender_init(asyncout, asyncfd) ;
  if (!textmessage_timed_send(asyncout, after, afterlen, deadline, stamp)) return 0 ;
  return 1 ;
}
