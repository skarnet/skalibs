/* ISC license. */

#include <skalibs/unirandom.h>
#include <skalibs/rrandom.h>

unsigned int rrandom_name (rrandom *z, char *s, unsigned int n, int nb)
{
  static char const *oklist = "ABCDEFGHIJKLMNOPQRSTUVWXYZghijklmnopqrstuvwxyz-_0123456789abcdef" ;
  register unsigned int r = rrandom_read(z, s, n, nb ? &unirandom_readnb : &unirandom_readb) ;
  register unsigned int i = 0 ;
  for (; i < r ; i++) s[i] = oklist[s[i] & 63] ;
  return r ;
}
