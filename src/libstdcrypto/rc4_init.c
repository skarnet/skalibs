/* ISC license. */
/* Thanks to Thomas Pornin <pornin@bolet.org> */

#include <skalibs/bytestr.h>
#include <skalibs/rc4.h>

void rc4_init (RC4Schedule_ref r, char const *key, unsigned int ksize)
{
  register unsigned int i = 0, j = 0 ;
  register unsigned char c = 0;

  r->x = r->y = 0 ;
  for (; i < 256 ; i++) r->tab[i] = i ;
  for (i = 0 ; i < 256 ; i++)
  {
    unsigned char t = r->tab[i] ;
    c = T8(c + (unsigned char)key[j] + t) ;
    r->tab[i] = r->tab[c] ;
    r->tab[c] = t ;
    if (++j == ksize) j = 0 ;
  }
  {
    char tmp[RC4_THROWAWAY] ;
    rc4(r, tmp, tmp, RC4_THROWAWAY) ;
  }
}
