/* ISC license. */

#include <skalibs/avlnode.h>

struct avlnode_iter_s
{
  avlnode const *s ;
  unsigned int max ;
  unsigned int cut ;
  avliterfunc_t_ref f ;
  void *p ;
} ;

static unsigned int avlnode_iter_rec (struct avlnode_iter_s const *blah, unsigned int r, unsigned int h)
{
  if (r >= blah->max) return blah->max ;
  {
    unsigned int res = avlnode_iter_rec(blah, blah->s[r].child[0], h+1) ;
    if (res != blah->max) return res ;
  }
  if (r == blah->cut) return blah->max ;
  if (!(*blah->f)(blah->s[r].data, h, blah->p)) return r ;
  return avlnode_iter_rec(blah, blah->s[r].child[1], h+1) ;
}

unsigned int avlnode_iter_nocancel (avlnode *s, unsigned int max, unsigned int cut, unsigned int r, avliterfunc_t_ref f, void *p)
{
  struct avlnode_iter_s blah = { .s = s, .max = max, .cut = cut, .f = f, .p = p } ;
  return avlnode_iter_rec(&blah, r, 0) ;
}
