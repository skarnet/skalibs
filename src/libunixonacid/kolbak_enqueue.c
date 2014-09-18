/* ISC license. */

#include <errno.h>
#include <skalibs/kolbak.h>
#include <skalibs/unixmessage.h>

int kolbak_enqueue (kolbak_queue_t *q, unixmessage_handler_func_t *f, void *data)
{
  register unsigned int newtail = (q->tail + 1) % q->n ;
  if (newtail == q->head) return (errno = ENOBUFS, 0) ;
  q->x[q->tail].f = f ;
  q->x[q->tail].data = data ;
  q->tail = newtail ;
  return 1 ;
}
