/* ISC license. */

#include <unistd.h>

#include <skalibs/djbunix.h>
#include <skalibs/posixplz.h>

#include "posixplz-internal.h"

static int f (char const *dst, mode_t mode, void *data)
{
  linkarg_t *la = data ;
  (void)mode ;
  return (*la->lf)(la->src, dst) ;
}

int mklinktemp (char const *src, char *dst, linkfunc_t_ref lf)
{
  linkarg_t la = { .lf = lf, .src = src } ;
  return mkfiletemp(dst, &f, 0600, &la) ;
}
