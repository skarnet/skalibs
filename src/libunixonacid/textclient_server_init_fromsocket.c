/* ISC license. */

#include <errno.h>
#include <string.h>
#include <sys/uio.h>

#include <skalibs/djbunix.h>
#include <skalibs/unix-timed.h>
#include <skalibs/ancil.h>
#include <skalibs/textmessage.h>
#include <skalibs/textclient.h>
#include <skalibs/posixishard.h>

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
  return ancil_send_fd(fd[0], fd[1], '|') ;
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
