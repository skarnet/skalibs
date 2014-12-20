/* ISC license. */

#include <skalibs/avlnode.h>

struct avlnode_iter_s
{
  avlnode *s ;
  unsigned int max ;
  avliterfunc_t_ref f ;
  void *p ;
} ;

static int avlnode_iter_rec (struct avlnode_iter_s const *blah, unsigned int r, unsigned int h)
{
  return (r < blah->max) ?
    avlnode_iter_rec(blah, blah->s[r].child[0], h+1)
    && (*blah->f)(blah->s[r].data, h, blah->p)
    && avlnode_iter_rec(blah, blah->s[r].child[1], h+1)
   : 1 ;
}

int avlnode_iter (avlnode *s, unsigned int max, unsigned int r, avliterfunc_t_ref f, void *p)
{
  struct avlnode_iter_s blah = { s, max, f, p } ;
  return avlnode_iter_rec(&blah, r, 0) ;
}
