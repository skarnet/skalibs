/* ISC license. */

#include <skalibs/skaclient.h>
#include <skalibs/tai.h>
#include <skalibs/unixmessage.h>

int skaclient_server_init (unixmessage_receiver_t *in, char *mainbuf, unsigned int mainlen, char *auxbuf, unsigned int auxlen, unixmessage_sender_t *out, unixmessage_sender_t *asyncout, char const *before, unsigned int beforelen, char const *after, unsigned int afterlen, tain_t const *deadline, tain_t *stamp)
{
  unixmessage_t m ;
  if (!unixmessage_receiver_init(in, 0, mainbuf, mainlen, auxbuf, auxlen)) return 0 ;
  unixmessage_sender_init(out, 1) ;
  if (unixmessage_timed_receive(in, &m, deadline, stamp) < 0) return 0 ;
  if (!skaclient_server_ack(&m, out, asyncout, before, beforelen, after, afterlen)) return 0 ;
  return unixmessage_sender_timed_flush(out, deadline, stamp) ;
}
