/* ISC license. */

#include <skalibs/skamisc.h>
#include <skalibs/djbunix.h>

int hiercopy (char const *src, char const *dst)
{
  return hiercopy_tmp(src, dst, &satmp) ;
}
