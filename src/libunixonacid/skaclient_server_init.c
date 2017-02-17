/* ISC license. */

#include <sys/types.h>
#include <skalibs/allreadwrite.h>
#include <skalibs/skaclient.h>
#include <skalibs/tai.h>
#include <skalibs/unixmessage.h>

int skaclient_server_init (unixmessage_receiver_t *in, unixmessage_sender_t *out, unixmessage_sender_t *asyncout, char const *before, size_t beforelen, char const *after, size_t afterlen, tain_t const *deadline, tain_t *stamp)
{
  unixmessage_t m ;
  return (sanitize_read(unixmessage_timed_receive(in, &m, deadline, stamp)) >= 0)
   && skaclient_server_ack(&m, out, asyncout, before, beforelen, after, afterlen)
   && unixmessage_sender_timed_flush(out, deadline, stamp) ;
}
