/* ISC license. */

#include <errno.h>
#include <skalibs/functypes.h>
#include <skalibs/gensetdyn.h>

int gensetdyn_iter_withcancel (gensetdyn *g, iterfunc_t_ref f, iterfunc_t_ref cancelf, void *stuff)
{
  unsigned int n = gensetdyn_iter(g, f, stuff) ;
  if (n < g->storage.len)
  {
    int e = errno ;
    gensetdyn_iter_nocancel(g, n, cancelf, stuff) ;
    errno = e ;
    return 0 ;
  }
  return 1 ;
}
