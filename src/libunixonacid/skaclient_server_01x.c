/* ISC license. */

/* MT-unsafe */

#include <skalibs/tai.h>
#include <skalibs/unixmessage.h>
#include <skalibs/skaclient.h>

int skaclient_server_01x_init (char const *before, unsigned int beforelen, char const *after, unsigned int afterlen, tain_t const *deadline, tain_t *stamp)
{
  return unixmessage_receiver_0_init() && skaclient_server_init(
    unixmessage_receiver_0,
    unixmessage_sender_1,
    unixmessage_sender_x,
    before,
    beforelen,
    after,
    afterlen,
    deadline,
    stamp) ;
}
