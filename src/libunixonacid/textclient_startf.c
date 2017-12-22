/* ISC license. */

#include <sys/uio.h>
#include <string.h>
#include <errno.h>
#include <skalibs/error.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/djbunix.h>
#include <skalibs/textmessage.h>
#include <skalibs/textclient.h>

int textclient_startf (textclient_t *a, char const *const *argv, char const *const *envp, uint32_t options, char const *before, size_t beforelen, char const *after, size_t afterlen, tain_t const *deadline, tain_t *stamp)
{
  struct iovec v ;
  int fd[3] ;
  pid_t pid = child_spawn(argv[0], argv, envp, fd, 3) ;
  if (!pid) return 0 ;
  textmessage_receiver_init(&a->syncin, fd[0], a->syncbuf, TEXTCLIENT_BUFSIZE, TEXTMESSAGE_MAXLEN) ;
  textmessage_receiver_init(&a->asyncin, fd[2], a->asyncbuf, TEXTCLIENT_BUFSIZE, TEXTMESSAGE_MAXLEN) ;
  textmessage_sender_init(&a->syncout, fd[1]) ;
  a->pid = pid ;
  a->options = options ;
  if (!textclient_exchange(a, before, beforelen, &v, deadline, stamp)) goto err ;
  if (v.iov_len != afterlen || memcmp(v.iov_base, after, afterlen)) goto errproto ;
  if (sanitize_read(textmessage_timed_receive(&a->asyncin, &v, deadline, stamp)) <= 0) goto err ;
  if (v.iov_len != afterlen || memcmp(v.iov_base, after, afterlen)) goto errproto ;
  return 1 ;

 errproto:
  errno = EPROTO ;
 err:
  textclient_end(a) ;
  return 0 ;
}
