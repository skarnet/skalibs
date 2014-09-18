/* ISC license. */

#include <skalibs/unixmessage.h>

int unixmessage_handle (unixmessage_receiver_t *b, unixmessage_handler_func_t *f, void *p)
{
  unsigned int n = UNIXMESSAGE_MAXREADS ;
  int count = 0 ;
  while (n--)
  {
    unixmessage_t m ;
    register int r = unixmessage_receive(b, &m) ;
    if (r < 0) return -1 ;
    if (!r) break ;
    if (!(*f)(&m, p)) return -2 ;
    count++ ;
  }
  return count ;
}
