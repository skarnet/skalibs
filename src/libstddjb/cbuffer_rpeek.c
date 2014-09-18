/* ISC license. */

#include <skalibs/cbuffer.h>
#include <skalibs/siovec.h>

void cbuffer_rpeek (cbuffer_t *b, siovec_t *v)
{
  v[0].s = b->x + b->p ;
  if (b->n >= b->p)
  {
    v[0].len = b->n - b->p ;
    v[1].s = 0 ;
    v[1].len = 0 ;
  }
  else
  {
    v[0].len = b->a - b->p ;
    v[1].s = b->x ;
    v[1].len = b->n ;
  }
}
