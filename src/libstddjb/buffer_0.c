/* ISC license. */

/* MT-unsafe */

#include <skalibs/buffer.h>

static char buf[BUFFER_INSIZE] ;
buffer buffer_0_ = BUFFER_INIT(&buffer_read, 0, buf, BUFFER_INSIZE) ;
