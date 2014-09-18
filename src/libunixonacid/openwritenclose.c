/* ISC license. */

/* MT-unsafe */

#include <skalibs/skamisc.h>
#include <skalibs/unix-transactional.h>

int openwritenclose (char const *fn, char const *s, unsigned int len)
{
  return openwritenclose_tmp(fn, s, len, &satmp) ;
}
