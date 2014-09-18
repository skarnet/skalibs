/* ISC license. */

#include <skalibs/avltreen.h>

int avltreen_insert (avltreen_ref t, unsigned int d)
{
  unsigned int i = avltreen_newnode(t, d) ;
  if (i >= avltreen_totalsize(t)) return 0 ;
  avltreen_insertnode(t, i) ;
  return 1 ;
}
