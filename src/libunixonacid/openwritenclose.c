/* ISC license. */

#include <skalibs/skamisc.h>
#include <skalibs/unix-transactional.h>

int openwritenclose (char const *fn, char const *s, size_t len)
{
  return openwritenclose_tmp(fn, s, len, &satmp) ;
}
