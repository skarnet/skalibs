/* ISC license. */

#include <errno.h>
#include <skalibs/kolbak.h>

int kolbak_queue_init (kolbak_queue_t *q, kolbak_closure_t *s, unsigned int len)
{
  if (len < 2) return (errno = EINVAL, 0) ;
  q->x = s ;
  q->n = len ;
  q->head = 0 ;
  q->tail = 0 ;
  return 1 ;
}
