/* ISC license. */

#include <skalibs/allreadwrite.h>
#include <skalibs/randomegd.h>

unsigned int randomegd_readb (int s, char *x, unsigned int n)
{
  unsigned int w = 0 ;
  unsigned int i = 0 ;
  for (; i < (n / 255) ; i++)
  {
    char const c[2] = { 0x02, 0xFF } ;
    register unsigned int wtmp ;
    if (allwrite(s, c, 2) < 2) return w ;
    wtmp = allread(s, x + w, 255) ;
    w += wtmp ;
    if (wtmp < 255) return w ;
  }
  if (w < n)
  {
    char c[2] = "\002" ;
    c[1] = n - w ;
    if (allwrite(s, c, 2) < 2) return w ;
    w += allread(s, x + w, c[1]) ;
  }
  return w ;
}
