/* ISC license. */

#include <errno.h>
#include <skalibs/avlnode.h>

int avlnode_iter_withcancel (avlnode *tree, unsigned int max, unsigned int root, avliterfunc_t_ref f, avliterfunc_t_ref cancelf, void *stuff)
{
  unsigned int cut = avlnode_iter_nocancel(tree, max, max, root, f, stuff) ;
  if (cut != max)
  {
    int e = errno ;
    avlnode_iter_nocancel(tree, max, cut, root, cancelf, stuff) ;
    errno = e ;
    return 0 ;
  }
  return 1 ;
}
