/* ISC license. */

#include <errno.h>
#include <skalibs/genset.h>

void genset_init (genset_ref x, void *storage, unsigned int *freelist, unsigned int esize, unsigned int max)
{
  register unsigned int i = 0 ;
  x->storage = (char *)storage ;
  x->freelist = freelist ;
  x->esize = esize ;
  x->max = max ;
  x->sp = max ;
  for (; i < max ; i++) freelist[i] = max - 1 - i ;
}

unsigned int genset_new (genset_ref x)
{
  return x->sp ? x->freelist[--x->sp] : (errno = ENOSPC, x->max) ;
}

int genset_delete (genset_ref x, unsigned int i)
{
  if ((i >= x->max) || (x->sp >= x->max)) return (errno = EINVAL, 0) ;
  x->freelist[x->sp++] = i ;
  return 1 ;
}
