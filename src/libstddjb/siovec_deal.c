/* ISC license. */

#include <skalibs/bytestr.h>
#include <skalibs/siovec.h>

unsigned int siovec_deal (siovec_t const *vj, unsigned int nj, siovec_t const *vi, unsigned int ni)
{
  unsigned int w = 0 ;
  unsigned int i = 0 ;
  unsigned int j = 0 ;
  unsigned int wi = 0 ;
  unsigned int wj = 0 ;
  while (i < ni && j < nj)
  {
    register unsigned int tor = vi[i].len - wi ;
    register unsigned int tow = vj[j].len - wj ;
    register unsigned int len = tor < tow ? tor : tow ;
    byte_copy(vj[j].s + wj, len, vi[i].s + wi) ;
    wi += len ; wj += len ; w += len ;
    if (wi >= vi[i].len) { wi = 0 ; i++ ; }
    if (wj >= vj[j].len) { wj = 0 ; j++ ; }
  }
  return w ;
}
