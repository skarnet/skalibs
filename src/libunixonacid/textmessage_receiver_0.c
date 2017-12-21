/* ISC license. */

/* MT-unsafe */

#include <stdint.h>
#include <skalibs/buffer.h>
#include <skalibs/textmessage.h>

static char buf[BUFFER_INSIZE] ;
textmessage_receiver_t textmessage_receiver_0_ = TEXTMESSAGE_RECEIVER_INIT(0, buf, BUFFER_INSIZE, UINT32_MAX) ;
