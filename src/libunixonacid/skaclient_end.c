/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/skaclient.h>
#include <skalibs/unixmessage.h>

void skaclient_end (skaclient_t *a)
{
  fd_close(a->syncout.fd) ;
  fd_close(a->asyncout.fd) ;
  unixmessage_sender_free(&a->syncout) ;
  unixmessage_sender_free(&a->asyncout) ;
  unixmessage_receiver_free(&a->syncin) ;
  unixmessage_receiver_free(&a->asyncin) ;
  if (a->pid && a->options & SKACLIENT_OPTION_WAITPID)
  {
    int wstat ;
    waitpid_nointr(a->pid, &wstat, 0) ;
  }
  *a = skaclient_zero ;
}
