/* ISC license. */

/* MT-unsafe */

#include <skalibs/buffer.h>

static char buf[BUFFER_OUTSIZE] ;
buffer buffer_1_ = BUFFER_INIT(&buffer_write, 1, buf, BUFFER_OUTSIZE) ;
