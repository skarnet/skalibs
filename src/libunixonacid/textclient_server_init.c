/* ISC license. */

#include <stdlib.h>
#include <skalibs/djbunix.h>
#include <skalibs/textclient.h>

int textclient_server_init (textmessage_receiver_t *in, textmessage_sender_t *syncout, textmessage_sender_t *asyncout, char const *before, size_t beforelen, char const *after, size_t afterlen, tain_t const *deadline, tain_t *stamp)
{
  return getenv(SKALIBS_CHILD_SPAWN_FDS_ENVVAR) ?
    textclient_server_init_frompipe(in, syncout, asyncout, before, beforelen, after, afterlen, deadline, stamp) :
    textclient_server_init_fromsocket(in, syncout, asyncout, before, beforelen, after, afterlen, deadline, stamp) ;
}
