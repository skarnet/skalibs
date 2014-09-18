/* ISC license. */

#include <skalibs/stralloc.h>
#include <skalibs/unixmessage.h>

void unixmessage_receiver_free (unixmessage_receiver_t *b)
{
  stralloc_free(&b->data) ;
  b->mainb.fd = -1 ;
  b->mainlen = b->auxlen = b->auxw = 0 ;
}
