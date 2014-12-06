/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/unixmessage.h>

void unixmessage_receiver_free (unixmessage_receiver_t *b)
{
  b->fd = -1 ;
  stralloc_free(&b->maindata) ;
  stralloc_free(&b->auxdata) ;
  b->mainlen = b->auxlen = 0 ;
}
