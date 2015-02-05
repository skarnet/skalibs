/* ISC license. */

/* MT-unsafe */

#include <skalibs/allreadwrite.h>
#include <skalibs/buffer.h>

static char buf[BUFFER_INSIZE_SMALL] ;
buffer buffer_0small_ = BUFFER_INIT(&fd_readsv, 0, buf, BUFFER_INSIZE_SMALL) ;
