/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/genalloc.h>
#include <skalibs/unixmessage.h>

void unixmessage_sender_init (unixmessage_sender_t *b, int fd)
{
  b->fd = fd ;
  b->data = stralloc_zero ;
  b->fds = genalloc_zero ;
  b->offsets = genalloc_zero ;
  b->head = 0 ;
  b->shorty = 0 ;
}
