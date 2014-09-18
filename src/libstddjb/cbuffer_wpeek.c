/* ISC license. */

#include <skalibs/cbuffer.h>
#include <skalibs/siovec.h>

void cbuffer_wpeek (cbuffer_t *b, siovec_t *v)
{
  unsigned int last = (b->a - 1 + b->p) % b->a ;
  v[0].s = b->x + b->n ;
  if (last >= b->n)
  {
    v[0].len = last - b->n ;
    v[1].s = 0 ;
    v[1].len = 0 ;
  }
  else
  {
    v[0].len = b->a - b->n ;
    v[1].s = b->x ;
    v[1].len = last ;
  }
}
