/* ISC license. */

#include <sys/uio.h>
#include <string.h>
#include <errno.h>

#include <skalibs/allreadwrite.h>
#include <skalibs/error.h>
#include <skalibs/webipc.h>
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

static ssize_t get (void *p)
{
  int *fd = p ;
  int r = ancil_recv_fd(fd[0], '|') ;
  if (r < 0) return error_isagain(errno) ? (errno = 0, 0) : r ;
  fd[1] = r ;
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
