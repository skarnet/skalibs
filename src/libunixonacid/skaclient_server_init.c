/* ISC license. */

#include <skalibs/skaclient.h>
#include <skalibs/tai.h>
#include <skalibs/unixmessage.h>

int skaclient_server_init (unixmessage_receiver_t *in, unixmessage_sender_t *out, unixmessage_sender_t *asyncout, char const *before, unsigned int beforelen, char const *after, unsigned int afterlen, tain_t const *deadline, tain_t *stamp)
{
  unixmessage_t m ;
  return (unixmessage_timed_receive(in, &m, deadline, stamp) >= 0)
   && skaclient_server_ack(&m, out, asyncout, before, beforelen, after, afterlen)
   && unixmessage_sender_timed_flush(out, deadline, stamp) ;
}
