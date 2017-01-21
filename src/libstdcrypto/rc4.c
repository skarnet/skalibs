/* ISC license. */
/* Thanks to Thomas Pornin <pornin@bolet.org> */

#include <sys/types.h>
#include <skalibs/bytestr.h>
#include <skalibs/rc4.h>

void rc4 (RC4Schedule *r, char const *in, char *out, size_t n)
{
  register size_t i = 0 ;
  for (; i < n ; i++)
  {
    register unsigned char t ;
    r->x = T8(r->x + 1) ;
    t = r->tab[r->x] ;
    r->y = T8(r->y + t) ;
    r->tab[r->x] = r->tab[r->y] ;
    r->tab[r->y] = t ;
    out[i] = (unsigned char)in[i] ^ T8(r->tab[r->x] + r->tab[r->y]) ;
  }
}
