/* ISC license. */

/* MT-unsafe */

#include <sys/types.h>
#include <skalibs/random.h>

void random_name (char *s, size_t n)
{
  static char const oklist[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZghijklmnopqrstuvwxyz-_0123456789abcdef" ;
  random_string(s, n) ;
  while (n--) s[n] = oklist[s[n] & 63] ;
}
