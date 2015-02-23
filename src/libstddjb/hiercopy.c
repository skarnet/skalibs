/* ISC license. */

#include <skalibs/djbunix.h>
#include <skalibs/skamisc.h>

int hiercopy (char const *src, char const *dst)
{
  return hiercopy_tmp(src, dst, &satmp) ;
}
