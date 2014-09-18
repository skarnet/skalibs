/* ISC license. */

/* MT-unsafe */

#include <skalibs/allreadwrite.h>
#include <skalibs/bufalloc.h>

static bufalloc b = BUFALLOC_INIT(&fd_write, 2) ;
bufalloc_ref bufalloc_2 = &b ;
