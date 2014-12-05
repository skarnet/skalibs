/* ISC license. */

/* MT-unsafe */

#include <skalibs/unixmessage.h>

static char mainbuf[UNIXMESSAGE_BUFSIZE] ;
static char auxbuf[UNIXMESSAGE_AUXBUFSIZE] ;

UNIXMESSAGE_RECEIVER_DECLARE_AND_INIT(unixmessage_receiver_0_, 0, mainbuf, UNIXMESSAGE_BUFSIZE, auxbuf, UNIXMESSAGE_AUXBUFSIZE) ;
