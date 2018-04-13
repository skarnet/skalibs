/* ISC license. */

#include <skalibs/functypes.h>
#include <skalibs/gensetdyn.h>

static int freeiter (char *s, void *aux)
{
  freefunc_t_ref f = aux ;
  (*f)((void *)s) ;
  return 1 ;
}

void gensetdyn_deepfree (gensetdyn *g, freefunc_t_ref f)
{
  gensetdyn_iter(g, &freeiter, f) ;
  gensetdyn_free(g) ;
}
