 /* ISC license. */

#include <skalibs/unixmessage.h>
#include <skalibs/unixconnection.h>

void unixconnection_init_withclosecb (unixconnection_t *io, int fdin, int fdout, unixmessage_sender_closecb_func_t_ref f, void *p)
{
  unixmessage_receiver_init(&io->in, fdin, io->mainbuf, UNIXMESSAGE_BUFSIZE, io->auxbuf, UNIXMESSAGE_AUXBUFSIZE) ;
  unixmessage_sender_init_withclosecb(&io->out, fdout, f, p) ;
}
