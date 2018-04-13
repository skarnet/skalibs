/* ISC license. */

#include <skalibs/functypes.h>
#include <skalibs/genset.h>

static int freeiter (char *s, void *aux)
{
  freefunc_t_ref f = aux ;
  (*f)((void *)s) ;
  return 1 ;
}

void genset_deepfree (genset *g, freefunc_t_ref f)
{
  genset_iter(g, &freeiter, f) ;
}
