/* ISC license. */

#include <skalibs/skaclient.h>
#include <skalibs/unixmessage.h>

int skaclient_server_bidi_ack (unixmessage_t const *clientmsg, unixmessage_sender_t *out, unixmessage_sender_t *asyncout, unixmessage_receiver_t *asyncin, char *mainbuf, unsigned int mainlen, char *auxbuf, unsigned int auxlen, char const *before, unsigned int beforelen, char const *after, unsigned int afterlen)
{
  if (!unixmessage_receiver_init(asyncin, -1, mainbuf, mainlen, auxbuf, auxlen)) return 0 ;
  if (!skaclient_server_ack(clientmsg, out, asyncout, before, beforelen, after, afterlen)) return 0 ;
  asyncin->mainb.fd = unixmessage_sender_fd(asyncout) ;
  return 1 ;
}
