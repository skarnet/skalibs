/* ISC license. */

/* MT-unsafe */

#include <skalibs/buffer.h>

static char buf[BUFFER_ERRSIZE] ;
buffer buffer_2_ = BUFFER_INIT(&buffer_write, 2, buf, BUFFER_ERRSIZE) ;
