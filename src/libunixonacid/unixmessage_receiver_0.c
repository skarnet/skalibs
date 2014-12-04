/* ISC license. */

/* MT-unsafe */

#include <skalibs/unixmessage.h>

static char mainbuf[UNIXMESSAGE_RECEIVER_MAINBUFSIZE] ;
static char auxbuf[UNIXMESSAGE_RECEIVER_AUXBUFSIZE] ;

unixmessage_receiver_t unixmessage_receiver_0_ = UNIXMESSAGE_RECEIVER_ZERO ;

int unixmessage_receiver_0_init ()
{
  return unixmessage_receiver_init(&unixmessage_receiver_0_, 0, mainbuf, UNIXMESSAGE_RECEIVER_MAINBUFSIZE, auxbuf, UNIXMESSAGE_RECEIVER_AUXBUFSIZE) ;
}
