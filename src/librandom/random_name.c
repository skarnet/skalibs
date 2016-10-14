/* ISC license. */

/* MT-unsafe */

#include <skalibs/random.h>

void random_name (char *s, unsigned int n)
{
  static char const oklist[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZghijklmnopqrstuvwxyz-_0123456789abcdef" ;
  random_string(s, n) ;
  while (n--) s[n] = oklist[s[n] & 63] ;
}
