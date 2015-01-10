/* ISC license. */

#include <skalibs/cbuffer.h>
#include <skalibs/stralloc.h>
#include <skalibs/djbunix.h>
#include <skalibs/unixmessage.h>

void unixmessage_receiver_free (unixmessage_receiver_t *b)
{
  register unsigned int h = b->maindata.len ;
  b->fd = -1 ;
  stralloc_free(&b->maindata) ;
  h = h != b->mainlen || b->auxdata.len != b->auxlen || cbuffer_len(&b->auxb) ;
  if (h)
  {
    register unsigned int n = b->auxdata.len / sizeof(int) ;
    while (n--) fd_close(((int *)b->auxdata.s)[n]) ;
  }
  stralloc_free(&b->auxdata) ;
  if (h)
  {
    register unsigned int n = cbuffer_len(&b->auxb) / sizeof(int) ;
    if (n)
    {
      int fds[n] ;
      cbuffer_get(&b->auxb, (char *)fds, n * sizeof(int)) ;
      while (n--) fd_close(fds[n]) ;
    }
  }
}
