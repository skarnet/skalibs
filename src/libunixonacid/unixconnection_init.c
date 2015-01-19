 /* ISC license. */

#include <skalibs/unixmessage.h>
#include <skalibs/unixconnection.h>

void unixconnection_init (unixconnection_t *io, int fdin, int fdout)
{
  unixmessage_receiver_init(&io->in, fdin, io->mainbuf, UNIXMESSAGE_BUFSIZE, io->auxbuf, UNIXMESSAGE_AUXBUFSIZE) ;
  unixmessage_sender_init(&io->out, fdout) ;
}
