/* ISC license. */

/* MT-unsafe */

#include <skalibs/allreadwrite.h>
#include <skalibs/bufalloc.h>

static bufalloc b = BUFALLOC_INIT(&fd_write, 1) ;
bufalloc_ref bufalloc_1 = &b ;
