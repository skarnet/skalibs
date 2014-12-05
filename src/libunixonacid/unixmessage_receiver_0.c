/* ISC license. */

/* MT-unsafe */

#include <skalibs/unixmessage.h>

static char mainbuf[UNIXMESSAGE_BUFSIZE] ;
static char auxbuf[UNIXMESSAGE_AUXBUFSIZE] ;

unixmessage_receiver_t unixmessage_receiver_0_ = UNIXMESSAGE_RECEIVER_ZERO ;

int unixmessage_receiver_0_init ()
{
  return unixmessage_receiver_init(&unixmessage_receiver_0_, 0, mainbuf, UNIXMESSAGE_BUFSIZE, auxbuf, UNIXMESSAGE_AUXBUFSIZE) ;
}
