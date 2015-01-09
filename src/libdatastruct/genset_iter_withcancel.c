/* ISC license. */

#include <errno.h>
#include <skalibs/functypes.h>
#include <skalibs/genset.h>

int genset_iter_withcancel (genset *g, iterfunc_t_ref f, iterfunc_t_ref cancelf, void *stuff)
{
  unsigned int n = genset_iter(g, f, stuff) ;
  if (n < g->max)
  {
    int e = errno ;
    genset_iter_nocancel(g, n, cancelf, stuff) ;
    errno = e ;
    return 0 ;
  }
  return 1 ;
}
